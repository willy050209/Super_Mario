#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "ObjectType.hpp"

class Object : public Util::GameObject {
public:
    Object() = delete;

    Object(const std::string& name, const std::shared_ptr<Core::Drawable>& drawable,
        const float zIndex = 10, const glm::vec2& pivot = { 0, 0 },
        const bool visible = true,
        const std::vector<std::shared_ptr<GameObject>>& children =
        std::vector<std::shared_ptr<GameObject>>())
        : GameObject(drawable, zIndex, pivot, visible, children), name(name) {
        
    }

    Object(const Object&) = delete;

    Object(Object&&) = delete;

    Object& operator=(const Object&) = delete;

    Object& operator=(Object&&) = delete;

    /// <summary>
    /// ���o Core::Drawable
    /// </summary>
    /// <returns>Core::Drawable</returns>
    inline std::shared_ptr<Core::Drawable> GetDrawable() const noexcept { return m_Drawable; }

    /// <summary>
    /// ���o�y��
    /// </summary>
    /// <returns>Position</returns>
    virtual inline const glm::vec2& GetPosition() const noexcept { return m_Transform.translation; }

    /// <summary>
    /// ���o�O�_�i��
    /// </summary>
    /// <returns>Visible</returns>
    inline bool GetVisibility() const noexcept { return m_Visible; }

    /// <summary>
    /// �]�w�y��
    /// </summary>
    /// <param name="Position">�y��</param>
    inline void SetPosition(const glm::vec2& Position) noexcept { m_Transform.translation = Position; }

    /// <summary>
    /// �]�w�Ϥ�
    /// </summary>
    /// <param name="ImagePath">�Ϥ����|</param>
    void setImage(const std::string& ImagePath) noexcept{ m_Drawable = std::make_shared<Util::Image>(ImagePath); }

    /// <summary>
    /// �P�_��J���x�άO�_�P�ۨ����|
    /// </summary>
    /// <param name="Position">�x�Τ��߮y��</param>
    /// <param name="size">�x�Τj�p</param>
    /// <returns></returns>
    inline bool inRange(const glm::vec2& Position, const glm::vec2& size) const noexcept {
		const auto& mpos = GetPosition();
		const auto& msize = GetSize();
		const auto&& _ml = mpos.x - (((int)msize.x) >> 1);
		const auto&& _mr = mpos.x + (((int)msize.x) >> 1);
		const auto&& _md = mpos.y - (((int)msize.y) >> 1);
		const auto&& _mu = mpos.y + (((int)msize.y) >> 1);
		const auto&& _ol = Position.x - (((int)size.x) >> 1);
		const auto&& _or = Position.x + (((int)size.x) >> 1);
		const auto&& _od = Position.y - (((int)size.y) >> 1);
		const auto&& _ou = Position.y + (((int)size.y) >> 1);
		/*
        const auto&& _ml = mpos.x - msize.x / 2;
		const auto&& _mr = mpos.x + msize.x / 2;
		const auto&& _md = mpos.y - msize.y / 2;
		const auto&& _mu = mpos.y + msize.y / 2;
		const auto&& _ol = Position.x - size.x / 2;
		const auto&& _or = Position.x + size.x / 2;
		const auto&& _od = Position.y - size.y / 2;
		const auto&& _ou = Position.y + size.y / 2;
        */
		return _ml < _or && _mr > _ol && _mu > _od && _md < _ou;
    }

    /// <summary>
    /// ���o�ۨ��j�p
    /// </summary>
    /// <returns>�x�Τj�p</returns>
    virtual inline glm::vec2 GetSize() const noexcept {
        return std::dynamic_pointer_cast<Util::Image>(m_Drawable)->GetSize();
    }

    /// <summary>
    /// �C������s�ɰ���
    /// </summary>
    /// <param name="data">GameManager *</param>
    virtual void behavior(void* data = nullptr) {}

    /// <summary>
    /// �O�_�i�I��
    /// </summary>
    bool collisionable{ true };

    /// <summary>
    /// �ۨ� ID
    /// </summary>
    std::string name;
    
	/// <summary>
	/// ���Ѧӥ~��Ʊ��f (void *)
	/// </summary>
	std::shared_ptr<void> userdata{ nullptr };

	/// <summary>
	/// �ۨ��������
	/// </summary>
	ObjectType MyType = ObjectType::Object;
};

#endif