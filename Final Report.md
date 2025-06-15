---
title: 2025 OOPL Final Report

---

# 2025 OOPL Final Report

報告若是可以的話，建議到 `hackmd` 查看，體驗較佳，報告連結：https://hackmd.io/@Generous/Supermario

## 組別資訊

組別：6  
組員：112340104黃紹泓、112590005陳宇威  
復刻遊戲：Super Mario Bros.  
專案連結：[點我](https://github.com/willy050209/Super_Mario "Super_Mario")  
遊玩影片：[留言區有重點，我弄很久，拜託看一下QAQ](https://www.youtube.com/watch?v=P7z0_l-20Nw)  

## 專案簡介

### 遊戲簡介

本遊戲共有三關，場景大致上為原本瑪利歐世界的1-1、1-2(沒有實作後方跳關環節)、1-4，在短暫 ~~(實作漫長)~~ 的三個關卡中，玩家將操控馬力歐穿梭於歷蘑菇王國 ~~(一堆水管跟香菇的奇怪地方，走一走還會掉進死人洞，莫名其妙)~~，在有限的生命數量內從大反派庫巴的魔掌裡救回我們的OOPL成績。

### 組別分工

* 112340104黃紹泓：素材尋找和產生、關卡詳情設計調整、地圖建構  
* 112590005陳宇威：表單框架、物件整體規劃

## 遊戲介紹

### 遊戲規則

**操控請使用英文輸入法和Windows環境**
使用方向鍵控制瑪利歐，可以達成左右跳蹲的動作，兩側`shift`鍵+移動可以加速奔跑，`esc`可以叫出選單，`ctrl`跟`shift`可以丟火球
**op模式：按`N`可以變成火焰瑪利歐、按`B`可以變大瑪利歐、按`T`可以即死、按下`O`之後可以進入無敵狀態，無敵狀態下不會受傷，可在地圖中漂浮移動，但只能左右(可加速)，無跳躍功能，上下仰賴`W`跟`S`鍵進行上下位置調整**

---
操控瑪利歐在時限內闖關1-1、1-2、1-4三關卡，在1-4 ~~打倒庫巴~~ 砍斷橋樑即可通關。

遊戲的1-2後方的跳關沒有實作，若是跳進去後果自負，**說不定有神祕的東西等著你**

遊戲過程中瑪利歐可以收集散落各處的金幣或敲擊特殊的磚塊，獲得其中的金幣或特殊道具。道具或金幣除了從正常的問號磚塊獲得，也會有隱藏的磚塊可以獲取更多的金幣或道具，千萬不要小看金幣，~~有了金幣瑪利歐才有錢賠償一路上破壞的蘑菇王國~~那些金幣累積到100可以幫瑪利歐加一條命。
道具方面瑪利歐可以獲得：
1. 超級蘑菇 ![BigMushroom](https://hackmd.io/_uploads/B1CGRxeQee.png=32x32)：吃了之後會瑪利歐會變大，可以多獲得一次承受敵人或障礙傷害的機會(受傷之後就縮水回去小矮人了)，此外在大瑪利歐的情況下還能將頭頂上的磚塊擊碎。
2. 火之花 ![frame0](https://hackmd.io/_uploads/Sk3YCxlQxe.png=32x32)：在大瑪利歐狀態下敲擊原本該出現超級蘑菇的位置會出現，拾取 ~~(吃下？)~~ 後瑪利歐可以丟出火焰擊弊敵人。
3. 無敵星 ![frame0](https://hackmd.io/_uploads/BynhRllXge.png)：拿到這個道具後，瑪利歐短暫 ~~化身超級賽亞人~~ 變成無敵狀態(約30S)，碰到他的敵人都會死去。
4. 1UP蘑菇 ![1upMushroom](https://hackmd.io/_uploads/S1WZ1Wl7gx.png)![1upMushroomDark](https://hackmd.io/_uploads/Bkb-1-gmeg.png)：拾取 ~~(應該不是吃下，那個看起來就有毒)~~ 後，瑪力歐會加一條命。

瑪利歐隻身穿梭於敵人中，跟敵人戰鬥的方法除了無敵星跟火之花，還有他那強壯的雙腳，瑪利歐可以透過雙腳踩死敵人，如果敵人是 ~~可愛的~~ 栗寶寶![frame0](https://hackmd.io/_uploads/BJOtgZxmle.png=32x32)則可以直接踩死(不覺得栗寶寶長得很像是香菇嗎，傳說栗寶寶原本也是磨菇王國的一員，後來因為不明原因倒戈投靠庫巴)，若是你遇到烏龜了![frame0](https://hackmd.io/_uploads/SycgbWe7gg.png=32x32)，那你也可以用你強大的雙腳踩他，他會縮進去龜殼中![KoopaTroopaShellGreen](https://hackmd.io/_uploads/B1WmbWeQll.png=32x32)，你可以將他踢走，就可以把龜殼撞向敵人或是磚塊破壞，當然瑪利歐自己碰到也會受傷，最後你可能會想問，庫巴呢，這可以踩嗎！
![frame0](https://hackmd.io/_uploads/S1ZffZlXex.png)

你看看他殼上的刺吧，你肯定不會想踩他的，最好的方法就是用智取，把橋砍斷讓他掉下去，但如果你是火焰狀態的瑪利歐，其實也可以用火焰擊斃他。

瑪利歐穿梭於蘑菇王國，破壞人家國家的方法，是使用堅硬的拳頭(頭部？)，瑪利歐處於大隻狀態的時候，向上跳撞擊，可以擊碎磚塊，除了可以找到一些隱藏在多個在磚塊中的神秘磚塊，也可以獲得高達50的分數喔。

講到分數，在遊戲中有各種獲得分數的方法，透過踩踏敵人、吃金幣、破壞磚塊、吃道具等方式都可以獲得不同的分數，每當分數連續不斷獲得或是累積到 $20,000$ 分或 $40,000$ 分時可以多獲得額外的一條命。

### 遊戲畫面
0. 瑪利歐的開場畫面  
![image](https://hackmd.io/_uploads/S1845mwXll.png)
1. 瑪利歐的暫停畫面  
![image](https://hackmd.io/_uploads/rJ75qmvmlx.png)

3. 歐的每次總結畫面(實際數字可能會依照實情變動)  
![supermario_pass_stage](https://hackmd.io/_uploads/B1OGrWlQgl.png)
3. 瑪利歐空降在1-1打亂人家的生活步調  
![image](https://hackmd.io/_uploads/ryWBjXDmgl.png)
5. 瑪利歐發現栗寶寶，然後被摸一下就沒命了  
![image](https://hackmd.io/_uploads/H1EAjQvmlg.png)

7. 瑪利歐鑽進水管探險1-1  
![image](https://hackmd.io/_uploads/ryxQhXPXxl.png)

11. 瑪利歐化身超級賽亞人  
![image](https://hackmd.io/_uploads/rJetn7DXxe.png)

14. 瑪利歐穿梭於火柱之間  
![image](https://hackmd.io/_uploads/SJo16XDXll.png)

15. 瑪利歐跟庫巴的對決  
![image](https://hackmd.io/_uploads/Sy-yC7wQgl.png)

16. 瑪利歐殘踩斷橋樑通關  
![image](https://hackmd.io/_uploads/rJb4Cmv7xg.png)




## 程式設計

### 程式架構
#### 表單
關於我們的遊戲專案開發，核心的實作是**表單**，表單的概念類似於視窗程式設計，表單在執行時的每一幀都會篩選目前應該出現的物件進行繪製顯示在畫面上
對於表單上發生的所有事件的發生，會根據篩選出來的物件，其屬性中的`behavior function`，判斷要不要執行。舉例來說，像是瑪利歐的移動，會表單會先篩選需要瑪利歐，接著去判斷瑪利歐的移動`behavior function`需要執行

```CPP=
INITFORM_FUNC(initForm1) {
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = "Form1";
	using MPATH = MyAPP::MyResourcesFilePath;
	
	//文字方塊
	{
		if (auto text = std::make_shared<TextObject>("label1", MPATH::ArialFontPath, 50, "hello world!", Util::Color(255, 255, 255))) {
			text->SetPosition({ 0, 0 });
			MyFM.addObject(formName, std::move(text));
		}
	}
	// 按鈕
	{
		auto buttoncallback = [](Button* const self, void* data) {
			std::cout << self->name << " is clicked!\n\r";
		};
		for (auto i = 0; i < 3; ++i) {
			auto button = std::make_shared<Button>(std::string("Button") + std::to_string(i), MPATH::ArialFontPath, 50, std::string("Button") + std::to_string(i), Util::Color(255, 255, 255));
			if (button == nullptr)
				continue;
			button->CallBackFunc = buttoncallback;
			button->SetPosition({ GetLeftEdge(button) + button->GetSize().x, GetTopEdge(button) - button->GetSize().y * i });
			MyFM.addObject(formName, std::move(button));
		}
	}
	// 圖片方塊
	{
		if (auto img = std::make_shared<ImageObject>("img", MY_RESOURCE_DIR "\\Image\\Background\\cat.jpg",1)) {
			img->SetPosition({ -GetLeftEdge(img), -GetTopEdge(img) });
			MyFM.addObject(formName, std::move(img));
		}
	}
	//事件
	{
		auto systemTime = [](EventObject*const self,void*data) {
			auto num = std::static_pointer_cast<int>(self->userdata);
			if ((*num)++ >= FPS_CAP) {
				auto currentTime = std::chrono::system_clock::now();
				auto time = std::chrono::system_clock::to_time_t(currentTime);
				std::cout << "目前時間：" << std::ctime(&time);
				(*num) = 0;
			}
		};
		if (auto timeEvent = std::make_shared<EventObject>("timeEvent", systemTime)) {
			timeEvent->userdata = std::make_shared<int>(0);
			MyFM.addObject(formName, std::move(timeEvent));
		}
	}
}
```


#### 物件
我們的物件關係如下  
![OOPL繼承關係.drawio](https://hackmd.io/_uploads/Hyhao7HXee.png)  
物件之間彼此繼承各自實作，再透過表單選擇需要的物件去呈現在畫面上

##### Character
遊戲中所有會動的角色交給`Character`物件來處理
##### EventObject
包含各種表單上的特殊事件，沒有多餘的屬性，只負責事件的實作，例如關卡中的時間倒數，由於只有在闖關過程會用到，不適合寫進`TextObject`中，故寫在`EventObject`

##### ImageObject
用於顯示圖片

##### TextObject
用於顯示文字

### 程式技術
#### 滑鼠點擊偵測
使用`C++`中的`SDL`函數，實踐滑鼠對畫面上的按鈕點擊，並執行相對應的操作，像是縮方比例、調整音量等
```cpp=
void Button::behavior(void* data) {
    int x, y;
    auto e = SDL_GetMouseState(&x, &y);
    if (inRange(Util::Input::GetCursorPosition(), { 1, 1 })) {
        setColor(ClickedColor);
        if (1 == SDL_BUTTON(e) && CallBackFunc) {
            trigger = true;
        }
    }
    else if (GetColor() == ClickedColor) {
        setColor(defultColor);
    }
    if (trigger && (SDL_BUTTON(e) == 0 || (unsigned)SDL_BUTTON(e) > 3)) {
        CallBackFunc(this, data);
        trigger = false;
    }
}
```


![WindowsTerminal_NA3Ut6xyii](https://hackmd.io/_uploads/rkF5prnQxg.gif)


#### 圖片縮放 & 多執行緒
因為在測試過程中發現遊戲畫面對有些人來說太小，於是我們撰寫了一個可以調整視窗大小並改縮放圖片的程式，撰寫完成後又發現執行過程太久，故使用了多執行緒的技巧進行優化
```cpp=
auto directorys = getSubdirectoriesRecursive(FOLDERPATH);

std::filesystem::create_directory("imgs");
std::vector<std::thread> threads;
for (auto& it : directorys) {
	std::string outpath = "imgs\\" + it.substr(sizeof(MY_RESOURCE_DIR));
	std::filesystem::create_directory(outpath);
	threads.push_back(std::thread([=]() {
		enlargeImages(it, (WINDOW_HEIGHT) / 480.f, outpath);
	}));
}
/*
執行其他初始化操作 
*/

//等待所有執行緒完成工作
for (auto& it : threads) {
	it.join();
}
```

#### function & void(* )轉換
我們會依照不同的`CALLCALLBACKFUN`實作不同功能，而因為每個函數需要傳入其中的參數型態數量都不盡相同，所以使用`self->userdata`其型別為`void(*)`打包，在各自的函數中解讀


```cpp=
#define EVENTCALLCALLBACKFUN(FUNC_name) static void FUNC_name(MyAPP::Form::Object::EventObject* const self, void* data)

EVENTCALLCALLBACKFUN(GetSystemTimeFunc) {
	auto num = std::static_pointer_cast<int>(self->userdata);
	if ((*num)++ >= FPS_CAP) {
		auto currentTime = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(currentTime);
		std::cout << "目前時間：" << std::ctime(&time);
		(*num) = 0;
	}
}
```

#### Singleton pattern & Lazy Initialization & Eager Initialization
對於 $\text{Singleton pattern}$：單例對象的類必須保證只有一個實例存在

$\text{Lazy Initialization}$：`BrickPositionReference`只會在`GetPositionReference()`第一次被呼叫時才創建。這比在程式啟動時就創建單例的 $\text{Eager Initialization}$ 方式更有效率，特別是當單例的創建成本較高且不一定會被用到時
```cpp=
/*
確保了創建的是一個 Brick 物件的唯一實例。
static 變數不只保證了只會被初始化一次，同時保證線程安全
從 C++11 開始，函數內的靜態局部變數的初始化是保證線程安全的。(本專案使用C++17)
*/
struct PositionReference {
	static const auto& GetPositionReference() {
		static ConstUniqueBrickPtr BrickPositionReference = std::make_unique<Brick>("", MyAPP::MyResourcesFilePath::BlockImagePath, 0);
		return BrickPositionReference;
	}

};
```
相比於上面的 $\text{Lazy Initialization}$ ，$\text{Eager Initialization}$ 是在程式碼一執行時就配置好記憶體，兩者並無絕對的優劣之分，端看使用當下的情況

```cpp=
class Fire :Interface::ICollisionable,Interface::IMovable,Interface::Iframes, public ImageObject {
public:
	...
	static constexpr auto GetFrames() { return Frame; }
private:
	static constexpr char* Frame[]{ R"(imgs\super mario\FireBall\01.png)", R"(imgs\super mario\FireBall\02.png)", R"(imgs\super mario\FireBall\03.png)", R"(imgs\super mario\FireBall\04.png)" };
	...
};
```

#### if constexpr
`if constexpr`允許在編譯時根據模板參數的特性來選擇執行不同的代碼塊。 
`if constexpr`在編譯階段就確定了要執行的分支，不符合條件的分支代碼會被編譯器完全丟棄，不會生成任何運行時開銷。

#### 類型特性 (Type Traits)

`std::is_same_v<Object::Mario, T>` 用於檢查 `T` 是否與`Object::Mario`類型完全相同。
`std::is_base_of_v<Object::Character, T>` 檢查 `T` 是否是 `Object::Character` 的子類（或者就是 `Object::Character` 本身）。
目的：這些類型特性在 `if constexpr` 中用作判斷條件，實現基於模板參數類型的靜態分派
```cpp=
template <typename T, class _Pr>
inline std::shared_ptr<T> GetFormObject_if(const std::string& formName, _Pr _Pred) const noexcept {
	auto form_it = m_Forms.find(formName);
	if (form_it == m_Forms.end()) {
		return nullptr;
	}
	auto& form = form_it->second;

	if constexpr (std::is_same_v<Object::Mario, T>) {
		auto it = std::find_if(form.m_Characters.begin(), form.m_Characters.end(), _Pred);
		if (it != form.m_Characters.end()) {
			return std::static_pointer_cast<Object::Mario>(*it);
		}
	}
	else if constexpr (std::is_base_of_v<Object::Character, T>) {
		auto it = std::find_if(form.m_Characters.begin(), form.m_Characters.end(), _Pred);
		if (it != form.m_Characters.end()) {
			return std::dynamic_pointer_cast<T>(*it);
		}
	}
	else if constexpr (std::is_base_of_v<Object::ImageObject, T>) {
		auto it = std::find_if(form.m_Images.begin(), form.m_Images.end(), _Pred);
		if (it != form.m_Images.end()) {
			return std::dynamic_pointer_cast<T>(*it);
		}
	}
	else if constexpr (std::is_same_v<Object::TextObject, T>) {
		auto it = std::find_if(form.m_Texts.begin(), form.m_Texts.end(), _Pred);
		return (it != form.m_Texts.end()) ? *it : nullptr;
	}
	else if constexpr (std::is_same_v<Object::Button, T>) {
		auto it = std::find_if(form.m_Buttons.begin(), form.m_Buttons.end(),_Pred;
		return (it != form.m_Buttons.end()) ? *it : nullptr;
	}
	else if constexpr (std::is_same_v<Object::EventObject, T>) {
		auto it = std::find_if(form.m_Events.begin(), form.m_Events.end(), _Pred);
		return (it != form.m_Events.end()) ? *it : nullptr;
	}

	return nullptr;
}
```

#### OOP 物件導向
##### 工廠方法 (Factory Method Pattern)
是一種實現了「工廠」概念的物件導向設計模式。就像其他建立型模式一樣，它也是處理在不指定對象具體類別的情況下建立對象的問題。工廠方法模式的實質是「定義一個建立對象的介面，但讓實現這個介面的類別來決定實例化哪個類別。工廠方法讓類別的實例化推遲到子類別中進行。」

```cpp=
[[nodiscard]] static CharacterPtr make_EnemysPtr(const Fileinfo& fileinfo) noexcept;

CharacterPtr MyAPP::Form::Object::MakeObject::make_EnemysPtr(const Fileinfo& fileinfo) noexcept {
	CharacterPtr enemy = nullptr;
	if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Goomba) {
		enemy = std::make_shared<Goomba>("Goomba", 20);
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Turtle) {
		enemy = std::make_shared<Turtle>("Turtle", 20);
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::Koopa) {
		enemy = std::make_shared<Koopa>("Koopa", 20);
	}
	else if (static_cast<ObjectType>(fileinfo.Type) == ObjectType::PiranaPlant) {
		enemy = std::make_shared<PiranaPlant>("PiranaPlant", 9);
		std::static_pointer_cast<PiranaPlant>(enemy)->SetPos(fileinfo.XY);
	}
	if (enemy) {
		enemy->SetPosition(fileinfo.XY);
		enemy->SetVisible(true);
		enemy->collisionable = fileinfo.Collisionable;
		enemy->setResetPosition(fileinfo.XY);
	}
	return enemy;
}
```

##### 封裝
封裝是將物件的屬性和操作該屬性的方法（行為）捆綁在一起，並對外部隱藏物件的內部細節。外部只能透過物件提供的公開介面來與之互動，也就是`public`、`private`、`protected`

像是在我們的專案中class FormManger 把表單做封裝，並提供插入、尋找、移除、切換表單等方法

##### 繼承

繼承允許一個類別（子類別）獲取另一個類別（父類別）的屬性與方法，實現了程式碼的重用

我們的專案中所有的物件都繼承Object(詳情可以看程式架構上面的圖片)

這可以避免類別中大量重複撰寫相同的程式碼

```cpp=
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
			const auto _ml = mpos.x - (msize.x / 2);
			const auto _mr = mpos.x + (msize.x / 2);
			const auto _md = mpos.y - (msize.y / 2);
			const auto _mu = mpos.y + (msize.y / 2);
			const auto _ol = Position.x - (size.x / 2);
			const auto _or = Position.x + (size.x / 2);
			const auto _od = Position.y - (size.y / 2);
			const auto _ou = Position.y + (size.y / 2);

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
// 事件物件 繼承Object
class EventObject : public Object{};
```

##### 多型
1. **子類型**
在我們的專案中所有的物件都繼承 `Object`，且會複寫 `behavior function` 在表單執行事件時會將所有物件轉為父類別 `Object`，在執行`behavior function`。
當透過父類別的呼叫這個方法時，實際執行的會是子類別中覆寫(`override`)過的方法

```cpp=
auto addEvent = [&](auto& it) {
	auto isInWindow = [](auto& it) {
		auto& pos = it->m_Transform.translation;
		auto size = it->GetSize();
		return std::abs(pos.x) - size.x <= WINDOW_WIDTH && std::abs(pos.y) - size.y <= WINDOW_HEIGHT;
	};
	if (isInWindow(it)) {
		m_Forms[nowForm].m_Form.m_Events.push_back(it);
	}
};
// 執行目前表單的事件
std::for_each(m_Forms[nowForm].m_Texts.begin(), m_Forms[nowForm].m_Texts.end(), addEvent);
std::for_each(m_Forms[nowForm].m_Buttons.begin(), m_Forms[nowForm].m_Buttons.end(), addEvent);
std::for_each(m_Forms[nowForm].m_Images.begin(), m_Forms[nowForm].m_Images.end(), addEvent);
std::for_each(m_Forms[nowForm].m_Characters.begin(), m_Forms[nowForm].m_Characters.end(), addEvent);
std::for_each(m_Forms[nowForm].m_Events.begin(), m_Forms[nowForm].m_Events.end(), addEvent);
doFormEvent(nowForm, data);
m_Forms[nowForm].m_Form.m_Events.clear();
```

2. **參數多型**
```cpp=
template <class T>
inline bool isInWindow(T* obj) {
	auto& pos = obj->m_Transform.translation;
	auto size = obj->GetSize();
	return std::abs(pos.x) - size.x <= WINDOW_WIDTH / 2 && std::abs(pos.y) - size.y <= WINDOW_HEIGHT / 2;
}
```

3. **特設多型**
一個多型函式可以應用於有不同類型的實際參數上，但是以來它們所應用到的實際參數類型而有不同的表現（也叫做為函式多載`function overloading`）
```cpp=
inline int GetLeftEdge(ObjectPtr obj) noexcept {
	return -((static_cast<int>(WINDOW_WIDTH) >> 1) - (static_cast<int>(obj->GetSize().x) >> 1));
}
template <class T>
inline int GetLeftEdge(T& obj) noexcept {
	return -((static_cast<int>(WINDOW_WIDTH) >> 1) - (static_cast<int>(obj->GetSize().x) >> 1));
}
template<class T>
inline int GetLeftEdge(T* obj) noexcept {
	return -((static_cast<int>(WINDOW_WIDTH) >> 1) - (static_cast<int>((obj)->GetSize().x) >> 1));
}
```

##### 介面
我們將物件的一部份功能給抽象化，使用介面實現。 
這裡使用struct來實作介面是因為C++ 的struct預設是公開繼承，這與介面的特性相符，所以介面都用struct取代class
```cpp=
namespace MyAPP::Form::Object::Interface {
	struct ICollisionable {
		virtual void CheckCollision(void* data) = 0;
	};
}
```



## 結語

### 問題與解決方法

本次開發過程中遇到諸多困難
1. 瑪利歐遊戲素材缺少
    在實作過程中，儘管有很多素材網站，但難免會有缺乏素材的情況，故我們使用`python`(ARGB色域轉換、檔案批次命名、`gif`批量轉為`png frame`、網路爬蟲下載音效等)跟小畫家等工具相互輔助，製作出缺乏的遊戲素材
3. 遊戲地圖建構 
     我們最初的想法是將地圖切成一格一格的方塊再進行排版，後發現有點不實際，於是改為以地圖當背景，把方塊放到對應的位置。
5. 火柱的各種問題
    原版的火柱以方塊為中心旋轉，PTSD似乎沒有提供圖片旋轉的方法。於是我們使用了暴力法，我們直接將我們找到的gif檔的每一幀拆解出來，再利用與火柱大小相同的方框當成火柱的碰撞箱，並在每次切換圖片時利用三角函數計算出應該出現的位置。
6. 地圖移動的問題
    Mario 移動有兩種可能，一種是Mario 保持在地圖中央，另一種是在地圖邊界時地圖不動讓Mario移動，但不能離開地圖。我們的解法是當Mario在地圖邊界時移動Mario，其餘狀態讓所有物件往Mario移動的相反方向走。
5. 取得表單物件
    在取得表單物件時因為C++的函數回傳值需要事先指定，所以在取得不同型態的物件時會發生問題，一開始的想法是一律回傳共通父類別，再自行轉換但就有誤操作產生，於是乎上我查詢了資料，改用`template` 搭配 `if constexpt` 實作。
6. 尋找表單物件
    最一開始的想法是用 `string` 儲存名字來辨識，但如果有一樣的名字，就會不確定會取得哪個物件。於是我們會在建立時給一個獨一無二的編號(~~雖然超過 `size_t` 的上限還是會重複，但應該不會有那麼多物件吧~~)，讓我們透過這編號尋找我們要的物件。
7. 效能問題1
    原本我們的架構會在表單重繪的時候，刷新所有物件，用我自己的桌機並沒有什麼問題，但是使用我的筆電時時常會發生卡頓(尤其是沒接電源時)。於是我們使用 `Visual Studio Diagnostic Tools` 分析CPU效能問題，發現是 `Util::GameObject::Draw` 佔的CPU time最高，於是我們加上了判別式判斷該物件是否位於畫面上再決定要不要繪製，便解決了此問題。
8. 效能問題2
    在使用 `Visual Studio Diagnostic Tools` 時意外發現在建立表單時記憶體會有個異常的上升在下降，仔細分析後我們發現是我們建立表時建立的`Pointer`與`vector`在傳遞給表單時，多複製了一份，後來我們使用了移動語意(Move Semantics)避免了資料傳遞時的性能開銷，有效降低了建立表單時的記憶體用量。
9. 延續效能問題2
    我們也發現了我們的Class 在實例化時有些變數會有重複建立的問題，例如圖片路徑，這種的變數並不會因為建立的不同的實例而有所改變，於是我們將這些變數更改為靜態成員變數（Static member variable）確保多個實例只有一個成員副本。

### 自評

| 項次 | 項目                   | 完成 |
|------|------------------------|-------|
| 1    | 這是範例 |  V  |
| 2    | 完成專案權限改為 public |  V  |
| 3    | 具有 debug mode 的功能  |  V  |
| 4    | 解決專案上所有 Memory Leak 的問題  |  V  |
| 5    | 報告中沒有任何錯字，以及沒有任何一項遺漏  |  V  |
| 6    | 報告至少保持基本的美感，人類可讀  |  V  |

### 心得

#### 112340104 黃紹泓
&#x3000;&#x3000;本次物件導向實習對我來說無疑是一大挑戰，由於從來沒有開發過大型專案的經驗，我在一開始的起步十分辛苦，幸好隊友人非常好，很有耐心，一步一步帶領我前進，幫我在程式碼上加上註解，花時間跟我講解，最後在彼此的合作下成功的完成了瑪利歐的遊戲復刻。  
&#x3000;&#x3000;本次實作讓我了解到專案開發命名、註解及合作的重要性，如果撰寫專案過程中隨意命名或是缺乏註解，很容易造成隊友或是幾天後的自己在解讀上的困擾。而團隊合作也需要彼此積極的溝通與交流，大家要互相彌補，才能一同完成專案的開發。
#### 112590005 陳宇威
&#x3000;&#x3000;這次的物件導向實習，我們接到了復刻一款遊戲的任務。起初，我認為這項挑戰並不會太困難，然而在實際開發的過程中，卻頻頻發現原本設計的架構不夠完善，許多未曾預料到的狀況接踵而來，促使我們必須不斷思考解決方案。

&#x3000;&#x3000;此外，與隊友協作時，也偶爾會遇到程式碼難以理解的情況，這讓我深刻體會到程式註解的重要性。總體而言，這次的遊戲復刻專案讓我實際體驗了專案開發的完整流程，從中獲益良多。
### 貢獻比例
* 112590005 陳宇威 55%
* 112340104 黃紹泓 45%

#    Contributor
**優秀的組員們**  
![Kapoo_100](https://hackmd.io/_uploads/B1MjYfoXlg.gif)
