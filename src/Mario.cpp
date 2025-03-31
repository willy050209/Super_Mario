#include "Mario.hpp"
#include "Object/ImageObject.hpp"
#include "Util/Input.hpp"
#include "config.hpp"
#include "FilePath.hpp"
#include "GameManager.hpp"

void Mario::behavior(void* data)
{
	if (!static_cast<GameManager*>(data)->pause) {
		// move();
		doJump();
		//if (state != State::DIED)
		comeDown();
	}
}

void Mario::doJump() noexcept
{
	if ((state == State::UP || (state == State::DIED && !diedflag)) && jumpDelay == 0) {
        auto tmp = GetPosition();
        auto blocks = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(userdata);
        tmp.y += displacement;
		if (state != State::DIED) {
			for (auto it = blocks->begin(); it < blocks->end(); ++it) {
				if ((*it)->collisionable && (*it)->inRange({ tmp.x, tmp.y }, GetSize())) {
					tmp.y = (*it)->GetPosition().y - (*it)->GetSize().y / 2 - GetSize().y / 2;
					if ((*it)->MyType == ObjectType::QuestionBlock) {
						std::static_pointer_cast<QuestionBlock>(*it)->bonk();
						/*(*it)->SetVisible(true);
						std::static_pointer_cast<Util::Image>((*it)->GetDrawable())->SetImage(EmptyBlockImagePath);
						(*it)->name = "EmptyBlock";*/
						// block->erase(it);
					}
					displacement = 0;
					jumpDelay = 0;
					break;
				}
			}
		}
		//changeImg();
        SetPosition(tmp);
        displacement -= (float)(DEFAULTDISPLACEMENT / 5);
		if (displacement < 0.1 ) {
			if (state != State::DIED)
				state = State::DOWN;
			else
				diedflag = true;
			index = 0;
            displacement = DEFAULTDISPLACEMENT;
        }
    }
    else if (jumpDelay > 0) {
        --jumpDelay;
    }
}

void Mario::comeDown()
{
    auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(userdata);
    bool flag = true;
    auto tmp = GetPosition();
	if (diedflag && state == State::DIED) {
		tmp.y -= displacement;
		SetPosition(tmp);
	}
	else if (state != State::UP && state != State::DIED && tmp.y < WINDOW_HEIGHT) {
        tmp.y -= displacement;
		const auto aaa = GetSize();
		for (auto& it : *bricks) {
			if (it->collisionable && it->inRange(tmp, aaa)) {
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
	index %= imgs[state][left].size();
	std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(imgs[state][left][index]);
}

void Mario::move(const float& d)
{
	imgChangeDelay++;
	if (imgChangeDelay >= 10) {
		index++;
		//index %= imgs[state][left].size();
		changeImg();
		imgChangeDelay = 0;
	}
}

void Mario::diedjump() noexcept{
		state = State::DIED;
		displacement = 2.5 * DEFAULTDISPLACEMENT;
		index = 0;
		jumpDelay = 0;
		changeImg();
		//state = State::UP;
}