#include "Object/Brick/QuestionBlock.hpp"
#include "config.hpp"
namespace MyAPP {
	namespace Form {
		namespace Object {
			void QuestionBlock::bonk() noexcept {
				if (play) {
					SetVisible(true);
					play = false;
					switch (color) {
					case MyAPP::Form::Object::BrickColor::normal:
						std::static_pointer_cast<Util::Image>(GetDrawable())
							->SetImage(MyAPP::MyResourcesFilePath::EmptyBlockImagePath);
						break;
					case MyAPP::Form::Object::BrickColor::dark:
						std::static_pointer_cast<Util::Image>(GetDrawable())
							->SetImage(MyAPP::MyResourcesFilePath::EmptyBlockDarkImagePath);
						break;
					case MyAPP::Form::Object::BrickColor::grey:
						std::static_pointer_cast<Util::Image>(GetDrawable())
							->SetImage(MyAPP::MyResourcesFilePath::EmptyBlockGreyImagePath);
						break;
					default:
						break;
					}
				}
			}

			void QuestionBlock::behavior(void* data) {
				 ();
				dojump();
				comeDown();
			}

			void QuestionBlock::PlayFrames() noexcept {
				if (play) {
					++(count);
					if (count >= (FPS_CAP / 5)) {
						++imgindex;
						imgindex %= 6;
						std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(GetFrame());
						count = 0;
					}
				}
			}
		}
	}
}