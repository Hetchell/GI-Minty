#pragma once

#include "../FunctionIncludes.h"
#include "../../game/filters.h"
#include "../../Utils/GuiUtils.h"

#include <mutex>
#include <queue>
#include <optional>

template<typename T>
class SafeQueue
{
public:
    SafeQueue() = default;
    SafeQueue(const SafeQueue<T>&) = delete;
    SafeQueue& operator=(const SafeQueue<T>&) = delete;

    SafeQueue(SafeQueue<T>&& other) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_ = std::move(other.queue_);
    }

    virtual ~SafeQueue() { }

    unsigned long size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    std::optional<T> pop()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return {};
        }
        T tmp = queue_.front();
        queue_.pop();
        return tmp;
    }

    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;

    bool empty() const {
        return queue_.empty();
    }
};

namespace cheat {
	class AutoLoot : public Function {
	public:
		ConfigField<bool> f_Enabled;

		ConfigField<bool> f_AutoPickup;
		ConfigField<bool> f_AutoTreasure;
		ConfigField<bool> f_UseCustomRange;
		ConfigField<bool> f_UseDelayTimeFluctuation;
		ConfigField<bool> f_PickupFilter;

		ConfigField<int> f_DelayTime;
		ConfigField<int> f_DelayTimeFluctuation;
		ConfigField<float> f_CustomRange;

		ConfigField<bool> f_Chest;
		ConfigField<bool> f_Leyline;
		ConfigField<bool> f_Investigate;
		ConfigField<bool> f_QuestInteract;
		ConfigField<bool> f_Others;

		ConfigField<bool> f_PickupFilter_Animals;
		ConfigField<bool> f_PickupFilter_DropItems;
		ConfigField<bool> f_PickupFilter_Resources;
		ConfigField<bool> f_PickupFilter_Oculus;

		Hotkey f_Hotkey;

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static AutoLoot& getInstance();
		bool isTeleportHotkeyPressed;

		AutoLoot();
	};
}
