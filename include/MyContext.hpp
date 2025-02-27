#ifndef MY_CONTEXT_HPP
#define MY_CONTEXT_HPP

#include "pch.hpp" // IWYU pragma: export

#include "config.hpp"

#include "Util/Time.hpp"

namespace Core {
    class Context {
    public:
        /**
         * @brief Initialize context for SDL, OpenGL, and create a window
         */
        Context(int w = WINDOW_WIDTH, int h = WINDOW_HEIGHT);
        Context(const Context&) = delete;
        Context(Context&&) = delete;

        ~Context();

        Context& operator=(const Context&) = delete;
        Context& operator=(Context&&) = delete;

        static std::shared_ptr<Context> GetInstance() noexcept;

        inline bool GetExit() const noexcept { return m_Exit; }
        inline unsigned int GetWindowWidth() const noexcept { return m_WindowWidth; }
        inline unsigned int GetWindowHeight() const noexcept { return m_WindowHeight; }
        inline SDL_Window* GetWindow() const noexcept { return m_Window; }
        inline SDL_bool GetFullScreenState() const noexcept { return fullScreenState; }

        inline void SetExit(bool exit) noexcept { m_Exit = exit; }
        inline void SetWindowWidth(unsigned int width) noexcept { m_WindowWidth = width; }
        inline void SetWindowHeight(unsigned int height) noexcept { m_WindowHeight = height; }
        inline void SetFullScreenState(SDL_bool&& sdl_bool) noexcept { fullScreenState = sdl_bool; }
        void SetWindowIcon(const std::string& path) noexcept;

        void ReSize(int w, int h) noexcept;
        void Setup() noexcept;
        void Update() noexcept;

    private:
        SDL_Window* m_Window;
        SDL_GLContext m_GlContext;
        SDL_bool fullScreenState = SDL_bool::SDL_FALSE;

        static std::shared_ptr<Context> s_Instance;
        bool m_Exit = false;

        unsigned int m_WindowWidth = WINDOW_WIDTH;
        unsigned int m_WindowHeight = WINDOW_HEIGHT;

        // Can't access Time::s_Now, so using this variable to track time.
        Util::ms_t m_BeforeUpdateTime = Util::Time::GetElapsedTimeMs();
    };

} // namespace Core

#endif //!MY_CONTEXT_HPP
