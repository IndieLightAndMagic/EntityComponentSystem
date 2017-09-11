/*
	Author : Tobias Stein
	Date   : 26th July, 2016
	File   : EventDelegate.h
	
	A  delegate to forward events to specific handler methdos.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __EVENT_DELEGATE_H__
#define __EVENT_DELEGATE_H__

#include "Platform.h"

namespace ECS { namespace Event {

	class IEvent;
	
	namespace Internal
	{
		using EventDelegateId = size_t;
	
	
		class IEventDelegate
		{
		public:
	
			virtual inline void invoke(const IEvent* const e) = 0;
	
			virtual inline EventDelegateId GetId() const = 0;
		}; // class IEventDelegate
	
		template<class Class, class EventType>
		class EventDelegate : public IEventDelegate
		{
			typedef void(Class::*Callback)(const EventType* const);
	
			Class* m_Receiver;
			Callback m_Callback;
	
		public:
	
			EventDelegate(Class* receiver, Callback& callbackFunction) :
				m_Receiver(receiver),
				m_Callback(callbackFunction)
			{}
	
			virtual inline void invoke(const IEvent* const e) override
			{
				if (e->GetReceiver() == INVALID_ENTITY_ID || e->GetReceiver() == this->m_Receiver->GetEntityId())
				{
					(m_Receiver->*m_Callback)(reinterpret_cast<const EventType* const>(e));
				}
			}
	
			virtual inline EventDelegateId GetId() const
			{
				return (EventDelegateId)&(*m_Receiver);
			}
		}; // class EventDelegate
	
	}
}} // namespace ECS::Event::Internal

#endif // __EVENT_DELEGATE_H__