#ifndef EVENTOBJECT_HPP
#define EVENTOBJECT_HPP

#include "Object.hpp"

class EventObject :public Object {

public:

    EventObject(const std::string& name, void (*CallBackFunc)(EventObject* const self, void* data) = nullptr,bool Enable = true)
        : Object(name, nullptr, 0, {0,0}, false, std::vector<std::shared_ptr<GameObject>>()), Enable(Enable) {
        this->CallBackFunc = CallBackFunc;
		MyType = ObjectType::EventObject;
    }

    EventObject(const EventObject&) = delete;

    EventObject(EventObject&&) = delete;

    EventObject& operator=(const EventObject&) = delete;

    EventObject& operator=(EventObject&&) = delete;

    inline void* GetCallBackFunc() const noexcept { return (void*)CallBackFunc; }

    inline void SetCallBackFunc(void (*CallBackFunc)(EventObject* const self, void* data)) noexcept { this->CallBackFunc = CallBackFunc; }

    virtual void behavior(void* data = nullptr) override {
        if(Enable && data)
            CallBackFunc(this, data);
    }

    bool Enable = true;

    void (*CallBackFunc)(EventObject* const self, void* data) = nullptr;
};

#endif