#include "Object/QuestionBlock.hpp"
#include "config.hpp"
namespace MyAPP {
	namespace Form {
		namespace Object {
			void QuestionBlock::bonk() noexcept {
				if (play) {
					SetVisible(true);
					play = false;
					std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(((blockState == EmptyBlockState::normal) ? *EmptyBlockImagePath : *EmptyBlockDarkImagePath));
				}
			}

			void QuestionBlock::behavior(void* data) {
				PlayFrames();
				dojump();
				comeDown();
			}

			void QuestionBlock::PlayFrames() noexcept {
				if (play) {
					++(count);
					if (count >= (FPS_CAP / 5)) {
						++imgindex;
						imgindex %= 6;
						std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(Frames[imgindex]);
						count = 0;
					}
				}
			}
		}
	}
}