#pragma once

namespace k5 {
	class Frame {
	public:
        Frame() = default;
        virtual ~Frame() = default;

		virtual void input() {};
		virtual void simulate() {};
		virtual void render() {};

        virtual void pause() {};
        virtual void resume() {};

        Frame(Frame&&) = delete;
		Frame& operator=(Frame&&) = delete;
		Frame(const Frame&) = delete;
		Frame& operator=(const Frame&) = delete;
	};
}
