#include "Object/Coin.hpp"
#include "config.hpp"
namespace MyAPP {
	namespace Form {
		namespace Object {
			void Coin::bonk() noexcept {
				if (play) {
					SetVisible(false);
					play = false;
					// std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(EmptyBlockImagePath);
				}
			}

			void Coin::behavior(void* data) {
				PlayGIF();
			}

			void Coin::PlayGIF() noexcept {
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