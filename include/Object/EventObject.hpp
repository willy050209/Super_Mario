#pragma once
#ifndef EVENTOBJECT_HPP
#define EVENTOBJECT_HPP

#include "Object.hpp"
#include <functional>

/// <summary>
/// 事件物件 繼承Object
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
    /// 取得CallBack Function
    /// </summary>
    /// <returns></returns>
	inline decltype(auto) GetCallBackFunc() const noexcept { return CallBackFunc; }

    /// <summary>
    /// 設定CallBack Function
    /// </summary>
    /// <param name="CallBackFunc"></param>
	inline void SetCallBackFunc(std::function<void(EventObject* const, void*)> CallBackFunc_) noexcept { this->CallBackFunc = CallBackFunc_; }

    /// <summary>
    /// 表單刷新時執行
    /// </summary>
    /// <param name="data"></param>
    virtual void behavior(void* data = nullptr) override {
        if(Enable && data)
            CallBackFunc(this, data);
    }

    /// <summary>
    /// 是否啟用事件
    /// </summary>
    bool Enable = true;

    std::function<void(EventObject* const, void*)> CallBackFunc = nullptr;
    //void (*CallBackFunc)(EventObject* const self, void* data) = nullptr;
};

#endif