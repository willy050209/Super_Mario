#ifndef EVENTOBJECT_HPP
#define EVENTOBJECT_HPP

#include "Object.hpp"

/// <summary>
/// �ƥ󪫥� �~��Object
/// </summary>
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

    /// <summary>
    /// ���oCallBack Function
    /// </summary>
    /// <returns></returns>
    inline void* GetCallBackFunc() const noexcept { return (void*)CallBackFunc; }

    /// <summary>
    /// �]�wCallBack Function
    /// </summary>
    /// <param name="CallBackFunc"></param>
    inline void SetCallBackFunc(void (*CallBackFunc)(EventObject* const self, void* data)) noexcept { this->CallBackFunc = CallBackFunc; }

    /// <summary>
    /// ����s�ɰ���
    /// </summary>
    /// <param name="data"></param>
    virtual void behavior(void* data = nullptr) override {
        if(Enable && data)
            CallBackFunc(this, data);
    }

    /// <summary>
    /// �O�_�ҥΨƥ�
    /// </summary>
    bool Enable = true;

    void (*CallBackFunc)(EventObject* const self, void* data) = nullptr;
};

#endif