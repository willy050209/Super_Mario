#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "ObjectType.hpp"

namespace MyAPP::Form:: Object {
	/// <summary>
	/// 提供所有物件的父類
	/// </summary>
	class Object : public Util::GameObject {
	public:
		Object() = delete;

		Object(const std::string& name, const std::shared_ptr<Core::Drawable>& drawable,
			const float zIndex = 10, const glm::vec2& pivot = { 0, 0 },
			const bool visible = true,
			const std::vector<std::shared_ptr<GameObject>>& children =
				std::vector<std::shared_ptr<GameObject>>())
			: GameObject(drawable, zIndex, pivot, visible, children), name(name) {
			m_ID = IDCounter++;
		}

		Object(const Object&) = delete;

		Object(Object&&) = delete;

		Object& operator=(const Object&) = delete;

		Object& operator=(Object&&) = delete;

		/// <summary>
		/// 取得 Core::Drawable
		/// </summary>
		/// <returns>Core::Drawable</returns>
		inline auto GetDrawable() const noexcept { return m_Drawable; }

		/// <summary>
		/// 取得座標
		/// </summary>
		/// <returns>Position</returns>
		virtual inline const glm::vec2& GetPosition() const noexcept { return m_Transform.translation; }

		/// <summary>
		/// 取得是否可見
		/// </summary>
		/// <returns>Visible</returns>
		inline bool GetVisibility() const noexcept { return m_Visible; }

		/// <summary>
		/// 設定座標
		/// </summary>
		/// <param name="Position">座標</param>
		inline void SetPosition(const glm::vec2& Position) noexcept { m_Transform.translation = Position; }

		/// <summary>
		/// 設定圖片
		/// </summary>
		/// <param name="ImagePath">圖片路徑</param>
		void setImage(const std::string& ImagePath) noexcept { m_Drawable = std::make_shared<Util::Image>(ImagePath); }

		inline void incPositionX(int Displacement) noexcept {
			m_Transform.translation.x += Displacement;
		}

		inline void incPositionY(int Displacement) noexcept {
			m_Transform.translation.y += Displacement;
		}

		/// <summary>
		/// 判斷輸入的矩形是否與自身重疊
		/// </summary>
		/// <param name="Position">矩形中心座標</param>
		/// <param name="size">矩形大小</param>
		/// <returns></returns>
		inline auto inRange(const glm::vec2& Position, const glm::vec2& size) const noexcept {
			const auto& mpos = GetPosition();
			const auto msize = GetSize();
			const int _ml = mpos.x - (int)(msize.x / 2);
			const int _mr = mpos.x + (int)(msize.x / 2);
			const int _md = mpos.y - (int)(msize.y / 2);
			const int _mu = mpos.y + (int)(msize.y / 2);
			const int _ol = Position.x - (int)(size.x / 2);
			const int _or = Position.x + (int)(size.x / 2);
			const int _od = Position.y - (int)(size.y / 2);
			const int _ou = Position.y + (int)(size.y / 2);

			return _ml < _or && _mr > _ol && _mu > _od && _md < _ou;
		}

		/// <summary>
		/// 取得自身大小
		/// </summary>
		/// <returns>矩形大小</returns>
		virtual inline glm::vec2 GetSize() const noexcept {
			return (m_Drawable) ? std::static_pointer_cast<Util::Image>(m_Drawable)->GetSize() : glm::vec2{ 0, 0 };
		}

		/// <summary>
		/// 每次表單刷新時執行
		/// </summary>
		/// <param name="data">GameManager *</param>
		virtual void behavior(void* data = nullptr) {}

				
		/// <summary>
		/// 自己的名子
		/// </summary>
		std::string name;

		/// <summary>
		/// 提供而外資料接口 (void *)
		/// </summary>
		std::shared_ptr<void> userdata{ nullptr };

		/// <summary>
		/// 自身資料類型
		/// </summary>
		ObjectType MyType = ObjectType::Object;

		/// <summary>
		/// 是否可碰撞
		/// </summary>
		bool collisionable{ true };

		/// <summary>
		/// 專屬於此物件的唯一編號(若物件數超過size_t的上限會重複)
		/// </summary>
		size_t m_ID;

	private:
		/// <summary>
		/// A static inline variable that holds a counter value, typically used for generating unique IDs.
		/// </summary>
		static inline size_t IDCounter{ 0 };
	};
}


#endif