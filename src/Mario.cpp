#include "Mario.hpp"
#include "Object/ImageObject.hpp"
#include "Util/Input.hpp"
#include "config.hpp"
#include "FilePath.hpp"
#include "GameManager.hpp"
#include <execution>
#include <mutex>

void Mario::behavior(void* data)
{
	if (!static_cast<GameManager*>(data)->pause && !static_cast<GameManager*>(data)->opMode) {
		// move();
		comeDown();
		doJump();
		//if (state != State::DIED)
	}
}

void Mario::doJump() noexcept
{
	if (jumpcount >0 && (state == State::UP || (state == State::DIED && !diedflag)) && jumpDelay == 0) {
		std::mutex displacement_mutex;
		std::mutex jumpDelay_mutex;
        auto tmp = GetPosition();
        auto blocks = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(userdata);
        tmp.y += displacement;
		if (state != State::DIED) {
			std::for_each(std::execution::seq,blocks->begin(), blocks->end(), [&](auto& it) {
				if ((it)->collisionable && (it)->inRange(tmp, GetSize())) {
					tmp.y = (it)->GetPosition().y - (static_cast<int>((it)->GetSize().y) >> 1) - (static_cast<int>(GetSize().y) >> 1);
					// if ((*it)->MyType == ObjectType::QuestionBlock) {
					//	std::static_pointer_cast<QuestionBlock>(*it)->bonk();
					//	/*(*it)->SetVisible(true);
					//	std::static_pointer_cast<Util::Image>((*it)->GetDrawable())->SetImage(EmptyBlockImagePath);
					//	(*it)->name = "EmptyBlock";*/
					//	// block->erase(it);
					// }
					(it)->bonk();
					(it)->bonkJump();

					{
						std::lock_guard<std::mutex> lock(displacement_mutex);
						displacement = 0;
					}
					{
						std::lock_guard<std::mutex> lock(jumpDelay_mutex);
						jumpDelay = 0;
					}
					//break;
				}
			});
		}
		//changeImg();
        SetPosition(tmp);
        /*displacement -= (float)(DEFAULTDISPLACEMENT / 5);*/
		jumpcount--;
		if (jumpcount == 0) {
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

void Mario::comeDown() noexcept
{
    auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(userdata);
    bool flag = true;
    auto tmp = GetPosition();
	if (diedflag && state == State::DIED) {
		tmp.y -= displacement*2;
		SetPosition(tmp);
	}
	else if (state != State::UP && state != State::DIED && tmp.y < WINDOW_HEIGHT) {
        tmp.y -= displacement*2;
		const auto MySize = GetSize();
		for (auto& it : *bricks) {
			if (it->collisionable && it->inRange(tmp, MySize)) {
				flag = false;
				tmp.y = it->GetPosition().y + (static_cast<int>(it->GetSize().y) >> 1) + (static_cast<int>(MySize.y) >> 1);
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

void Mario::move() noexcept
{
	imgChangeDelay++;
	if (imgChangeDelay >= 10) {
		index++;
		//index %= imgs[state][left].size();
		changeImg();
		imgChangeDelay = 0;
	}
}

void Mario::died() noexcept{
		state = State::DIED;
		displacement = 2.5 * DEFAULTDISPLACEMENT;
		index = 0;
		jumpDelay = 0;
		changeImg();
		//state = State::UP;
}

