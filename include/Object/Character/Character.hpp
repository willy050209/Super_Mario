#pragma once
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Util/GameObject.hpp"
#include "Object.hpp"
#include "config.hpp"

namespace MyAPP {
	namespace Form {
		namespace Object {
			
			
			static inline auto& getDEFAULTDISPLACEMENT() noexcept {
				static const auto DEFAULTDISPLACEMENT = WINDOW_HEIGHT / 15.f / 10 ;
				return DEFAULTDISPLACEMENT;
			}

			/// <summary>
			/// �Ҧ����⪺�����O �~��Object
			/// </summary>
			class Character : public Object {
			public:
				explicit Character(const std::string& name, const std::string& ImagePath, int zindex)
					: Object(name, std::make_shared<Util::Image>(ImagePath), zindex) {
					MyType = ObjectType::Character;
				}


				Character(const Character&) = delete;

				Character(Character&&) = delete;

				Character& operator=(const Character&) = delete;

				Character& operator=(Character&&) = delete;

				/*inline bool IfCollides(const std::shared_ptr<Object::Character>& other) const noexcept {
					return fabs(other->GetPosition().x - GetPosition().x) <= 10.0 && fabs(other->GetPosition().y - GetPosition().y) <= 10.0;

				}*/

				/// <summary>
				/// �O�_���V����
				/// </summary>
				/// <returns></returns>
				inline auto isLeft() const noexcept {
					return left == 1;
				}

				/// <summary>
				/// �]�w�V���V�k
				/// </summary>
				/// <typeparam name="val">true �V�� false �V�k</typeparam>
				template<bool T_or_F>
				inline void SetLeft() noexcept {
					if constexpr (T_or_F) {
						left = 1;
					}
					else {
						left = 0;
					}
				}

				/// <summary>
				/// ���`�ƥ�
				/// </summary>
				virtual void died() noexcept = 0;

				/// <summary>
				/// ���ʨƥ�
				/// </summary>
				virtual void move() noexcept;

				virtual void Reset() noexcept {
					m_Visible = true;
					collisionable = true;
					ResetPosition();
					SetLeft<true>();
				}

				inline auto setResetPosition(const glm::vec2& pos) noexcept { ResetPositionValue = pos; }

				inline const auto& getResetPosition() const noexcept { return ResetPositionValue; }

				const auto getBottom() const noexcept {
					return GetPosition().y - GetSize().y / 2;
				}

			protected:
				/// <summary>
				/// ���]�y��
				/// </summary>
				inline void ResetPosition() noexcept { m_Transform.translation = ResetPositionValue; }

				/// <summary>
				/// �Y���ƥ�
				/// </summary>
				virtual void comeDown() noexcept;

				/// <summary>
				/// �V���X��
				/// </summary>
				int left = 0;

				glm::vec2 ResetPositionValue = { 0, 0 };
			};
		}
	}
}
#endif // !CHARACTER_HPP
