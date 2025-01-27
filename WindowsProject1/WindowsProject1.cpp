#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

// Пути к изображениям
const wchar_t* IMAGE_PATHS[] = {
    L"D:\\mashasoska\\image1.jpg",
    L"D:\\mashasoska\\image2.jpg",
    L"D:\\mashasoska\\image3.jpg",
    L"D:\\mashasoska\\image4.jpg",
    L"D:\\mashasoska\\image5.jpg"
};

Image* currentImage = nullptr;

void LoadImageByIndex(int index) {
    if (index < 0 || index >= 5) return;

    delete currentImage;
    currentImage = new Image(IMAGE_PATHS[index]);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND: {
        int id = LOWORD(wParam); // Получить ID кнопки
        LoadImageByIndex(id - 1);
        InvalidateRect(hwnd, NULL, TRUE); // Перерисовать окно
        break;
    }
    case WM_ERASEBKGND: { // Установка цвета фона
        HDC hdc = (HDC)wParam;
        RECT rect;
        GetClientRect(hwnd, &rect);
        HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255)); // Белый цвет
        FillRect(hdc, &rect, brush);
        DeleteObject(brush);
        return 1; // Указывает, что фон обработан
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        if (currentImage) {
            Graphics graphics(hdc);

            // Получение размеров окна
            RECT rect;
            GetClientRect(hwnd, &rect);
            int windowWidth = rect.right - rect.left;
            int windowHeight = rect.bottom - rect.top;

            // Получение размеров изображения
            int imgWidth = currentImage->GetWidth();
            int imgHeight = currentImage->GetHeight();

            // Вычисление координат для центрирования
            int x = (windowWidth - imgWidth) / 2;
            int y = (windowHeight - imgHeight) / 2;

            // Рисуем изображение
            graphics.DrawImage(currentImage, x, y, imgWidth, imgHeight);
        }

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        delete currentImage; 
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    const wchar_t CLASS_NAME[] = L"SimpleWinApp";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Выбор девушки",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 1000,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd) return 0;

    // Создание кнопок
    HWND hButton1 = CreateWindow(
        L"BUTTON",
        L"💖 Самая красивая 💖",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        10, 10, 200, 50,
        hwnd,
        (HMENU)1,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND hButton2 = CreateWindow(
        L"BUTTON",
        L"🧠 Самая умная 🧠",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        220, 10, 200, 50,
        hwnd,
        (HMENU)2,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND hButton3 = CreateWindow(
        L"BUTTON",
        L"✨ Самая харизматичная ✨",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        430, 10, 200, 50,
        hwnd,
        (HMENU)3,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND hButton4 = CreateWindow(
        L"BUTTON",
        L"🔥 С красивой фигурой 🔥",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        640, 10, 200, 50,
        hwnd,
        (HMENU)4,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    HWND hButton5 = CreateWindow(
        L"BUTTON",
        L"❤️ Самая лучшая ❤️",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        850, 10, 200, 50,
        hwnd,
        (HMENU)5,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Завершение работы GDI+
    GdiplusShutdown(gdiplusToken);

    return 0;
}