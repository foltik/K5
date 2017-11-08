#pragma once
#include <k5/k5.h>

class MainFrame : public IFrame {
public:
    static MainFrame& Instance() {
        static MainFrame instance;
        return instance;
    }

	MainFrame(const MainFrame&) = delete;
    MainFrame(MainFrame&&) = delete;
    void operator=(const MainFrame&) = delete;
    void operator=(MainFrame&&) = delete;

	void Init() override;
    void Cleanup() override;

    void Pause() override;
    void Resume() override;

    void ProcessInput(bool keyboard[512], bool mouse[16], double mxpos, double mypos) override;
    void Loop() override;
    void Render(RenderEngine& renderEngine) override;

protected:
    MainFrame() = default;
};
