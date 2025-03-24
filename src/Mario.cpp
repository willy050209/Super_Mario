#include "Mario.hpp"
#include "Object/ImageObject.hpp"
#include "Util/Input.hpp"
#include "config.hpp"

void Mario::behavior(void* data)
{
    //move();
    doJump();
    comeDown();
}

void Mario::doJump() noexcept
{
    if (state == State::UP && jumpDelay == 0) {
        auto tmp = GetPosition();
        auto block = std::static_pointer_cast<std::vector<std::shared_ptr<ImageObject>>>(userdata);
        tmp.y += displacement;
        for (auto it = block->begin(); it < block->end(); ++it) {
			if ((*it)->inRange({ tmp.x, tmp.y},GetSize())) {
				tmp.y = (*it)->GetPosition().y - (*it)->GetSize().y / 2 - GetSize().y / 2;
                if ((*it)->name == "QuestionBlock") {
                    (*it)->SetVisible(false);
					block->erase(it);
                }
                displacement = 0;
                jumpDelay = 15;
                break;
            }
        }
		//changeImg();
        SetPosition(tmp);
        displacement -= (float)(DEFAULTDISPLACEMENT / 5);
        if (displacement < 0.1) {
            state = State::DOWN;
			index = 0;
            displacement = DEFAULTDISPLACEMENT;
        }
    }
    else if (jumpDelay > 0) {
        --jumpDelay;
    }
}

void Mario::comeDown() noexcept
{
    auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<ImageObject>>>(userdata);
    bool flag = true;
    auto tmp = GetPosition();
    if (state != State::UP && tmp.y < WINDOW_HEIGHT) {
        tmp.y -= displacement;
		const auto aaa = GetSize();
        for (auto& it : *bricks) {
			if (it->inRange(tmp, aaa)) {
                flag = false;
				tmp.y = it->GetPosition().y + it->GetSize().y;
				break;
            }
        }
		SetPosition(tmp);
        if(flag)
        {
			state = State::DOWN;
        }
        else
        {
			if (state != State::MOVE) {
				if (state == State::UP)
					index = 0;
				state = State::MOVE;
				changeImg();
			}
			
        }
    }
}

void Mario::changeImg() noexcept {
	std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(imgs[state][left][index]);
}

void Mario::move(const float& d)
{
	imgChangeDelay++;
	if (imgChangeDelay >= 10) {
		index++;
		index %= imgs[state][left].size();
		changeImg();
		imgChangeDelay = 0;
	}
}
