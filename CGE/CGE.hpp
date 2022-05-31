#pragma once
#include <Windows.h>
#include <string>
#include "ConsoleWindow.hpp"
#include "Delegate.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "Resource.hpp"

class CGE
{
public:

    // Begin ticking.
    static void Run( const Action<>& a_Action )
    {
        s_Running = true;
        Input::Initialize();

        while ( s_Running )
        {
            a_Action.Invoke();

            // Update calls.
            Input::Tick();
            Time::Tick();
            
            // Draw calls.
            ConsoleWindow::SwapBuffers( ConsoleWindow::GetCurrentContext() );

            // Console Window
            if ( s_ShowFPS )
            {
                //float FPS = Time::GetFPS();
                //ConsoleWindow::SetTitle( std::to_string((int)FPS).c_str() );
            }
        }

        Input::Deinitialize();
    }

    static bool SetLockedFPS( float a_LockedFPS )
    {
        //s_LockedFPS = 1000.0f / a_LockedFPS;
    }

    static bool Quit()
    {
        if ( !s_Running )
        {
            return false;
        }

        s_Running = false;
        return true;
    }

    inline static bool IsRunning()
    {
        return s_Running;
    }

    /*inline static void ShowFPS( bool a_Value )
    {
        s_ShowFPS = a_Value;
    }

    inline static void SetTargetFPS( float a_Value )
    {
        s_TargetFPS = Math::Max( a_Value, 0.0f );

        if ( s_TargetFPS )
        {
            s_TargetDeltaTime = 1.0f / s_TargetFPS;
        }
    }

    inline static float GetTargetFPS()
    {
        return s_TargetFPS;
    }*/

private:

    /*static void PadDeltaTime()
    {
        if ( s_TargetFPS )
        {
            float RealDeltaTime = Time::GetRealDeltaTime();

            if ( RealDeltaTime < s_TargetDeltaTime )
            {
                Sleep( 1000.0f * ( s_TargetDeltaTime - RealDeltaTime ) );
            }
        }
    }*/

    static bool  s_Running;
    static bool  s_ShowFPS;
    static float s_TargetFPS;
    static float s_TargetDeltaTime;
};