#include<Windows.h>
#include<stdio.h>
#include "res.h"
#include <cstdlib>

bool isGameOnn = true;
bool isFirstPlayer = true;
int pola[3][3];
bool krzyzykWygral = false;
int licznik = 0;
void wyczysc(HWND hwndDlg);
void narysuj(HWND hwndDlg);
bool isFieldOccupiedByFirstPlayer[3][3];
bool isFieldOccupiedBySecondPlayer[3][3];

 void wyczysc(HWND hwndDlg)
 {
   HDC hdcOkno = GetDC(hwndDlg);
   HBRUSH PedzelBia, Pudelko;

   PedzelBia = CreateSolidBrush(0xFFFFFF);

   Pudelko = (HBRUSH)SelectObject(hdcOkno, PedzelBia);

   Rectangle(hdcOkno, 40, 40, 340, 340);
   SelectObject(hdcOkno, Pudelko);

   DeleteObject(PedzelBia);
   ReleaseDC(hwndDlg, hdcOkno);
 }
 
 void narysuj(HWND hwndDlg)
 {
   CHAR szText[500];
   HDC hdc = GetDC(hwndDlg);
   HPEN hMyPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
   SelectObject(hdc, hMyPen);
   MoveToEx(hdc, 40, 140, NULL);
   LineTo(hdc, 340, 140);
   MoveToEx(hdc, 40, 240, NULL);
   LineTo(hdc, 340, 240);
   MoveToEx(hdc, 140, 40, NULL);
   LineTo(hdc, 140, 340);
   MoveToEx(hdc, 240, 40, NULL);
   LineTo(hdc, 240, 340);
   DeleteObject(hMyPen);
   wsprintf(szText, "Aby wykonaæ ruch klikaj na planszy");
   TextOut(hdc, 0, 0, szText, strlen(szText));
   ReleaseDC(hwndDlg, hdc);
 }


bool wygrana()
{
  int zmienna = -10;
  for (int i = 0; i < 3; i++)
  {
    if ((pola[i][0]==pola[i][1]) && (pola[i][0]==pola[i][2]) && (pola[i][0] != -1))
    {
      isGameOnn = false;
      if (pola[i][0] == 1)
      {
        krzyzykWygral = true;
      }
      return true;
    }
  }
  for (int i = 0; i < 3; i++)
  {
    if ((pola[0][i] == pola[1][i]) && (pola[0][i] == pola[2][i]) && (pola[0][i] != -1))
    {
      isGameOnn = false;
      if (pola[0][i] == 1)
      {
        krzyzykWygral = true;
      }
      return true;
    }
  }
  if ((pola[0][0] == pola[1][1]) && (pola[0][0] == pola[2][2]) && (pola[1][1] != -1))
  {
    isGameOnn = false;
    if (pola[0][0] == 1)
    {
      krzyzykWygral = true;
    }
    return true;
  }
  if ((pola[2][0] == pola[1][1]) && (pola[2][0] == pola[0][2]) && (pola[1][1] != -1))
  {
    isGameOnn = false;
    if (pola[1][1] == 1)
    {

      krzyzykWygral = true;
    }
    return true;
  }
  return false;
}






INT_PTR CALLBACK DialogProc(HWND hwndDig, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:

    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {


      case IDC_BUTTON10:
        krzyzykWygral = false;
        isFirstPlayer = true;
        isGameOnn = true;
        licznik = 0;
        CheckRadioButton(hwndDig, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
        HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
        CHAR szText[500];
        wsprintf(szText, "");
        SetWindowText(hwndStatic, szText);

        for (int i = 0; i < 3; i++)
        {
          for (int j = 0; j < 3; j++)
          {
            isFieldOccupiedByFirstPlayer[i][j] = false;
            isFieldOccupiedBySecondPlayer[i][j] = false;
            pola[i][j] = -1;
          }

        }

        wyczysc(hwndDig);
        narysuj(hwndDig);

        return TRUE;
      }

      return FALSE;

    }


    return FALSE;
  case WM_LBUTTONDOWN:
    if (isGameOnn == true && licznik < 9)
    {
      HDC hdc = GetDC(hwndDig);
      int x = LOWORD(lParam);
      int y = HIWORD(lParam);
      if ((x > 40 && x < 340) && (y > 40 && y < 340))
      {
        int FieldX = ((x - 40) / 100);
        int FieldY = ((y - 40) / 100);
        if (isFieldOccupiedByFirstPlayer[FieldX][FieldY] == false && isFieldOccupiedBySecondPlayer[FieldX][FieldY] == false)
        {

          x = ((x - 40) / 100) * 100 + 90;
          y = ((y - 40) / 100) * 100 + 90;
          if (isFirstPlayer == true)
          {
            MoveToEx(hdc, x - 30, y - 30, NULL);
            LineTo(hdc, x + 30, y + 30);
            MoveToEx(hdc, x - 30, y + 30, NULL);
            LineTo(hdc, x + 30, y - 30);
            isFieldOccupiedByFirstPlayer[FieldX][FieldY] = true;
            CheckRadioButton(hwndDig, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
            pola[FieldX][FieldY] = 1;
            licznik++;

          }
          else
          {

            HBRUSH PedzelZiel, Pudelko;
            PedzelZiel = CreateSolidBrush(0x00FF00);
            Pudelko = (HBRUSH)SelectObject(hdc, PedzelZiel);
            Ellipse(hdc, x-30, y-30, x+30, y+30);
            SelectObject(hdc, Pudelko);
            DeleteObject(PedzelZiel);
            ReleaseDC(hwndDig, hdc);


            isFieldOccupiedBySecondPlayer[FieldX][FieldY] = true;
            CheckRadioButton(hwndDig, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
            pola[FieldX][FieldY] = 0;
            licznik++;
          }
          ReleaseDC(hwndDig, hdc);
          isFirstPlayer = !isFirstPlayer;

          if (wygrana() == true)
          {
            isGameOnn = false;
            if (krzyzykWygral == true)
            {
              HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
              CHAR szText[500];
              wsprintf(szText, "Brawo pierwszy gracz wygra³, aby zagraæ ponownie - restart");
              SetWindowText(hwndStatic, szText);
            }
            else
            {
              HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
              CHAR szText[500];
              wsprintf(szText, "Brawo drugi gracz wygra³, aby zagraæ ponownie - restart");
              SetWindowText(hwndStatic, szText);
            }
          }
        }
        if ((licznik == 9) && (wygrana() == false))
        {
          isGameOnn = false;
          HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
          CHAR szText[500];
          wsprintf(szText, "Brak roztrzygniêcia - restart");
          SetWindowText(hwndStatic, szText);
        }


      }
    }


  return TRUE;

  case WM_CLOSE:
    DestroyWindow(hwndDig);
    PostQuitMessage(0);
    return TRUE;
  }
  return FALSE;
}



int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, PSTR szCmdLIne, int iCmdShow)
{


  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      isFieldOccupiedByFirstPlayer[i][j] = false;
      isFieldOccupiedBySecondPlayer[i][j] = false;
      pola[i][j] = -1;
    }
  }
  HWND hwndMainWindow = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  MSG msg = {};
  CheckRadioButton(hwndMainWindow, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
  wyczysc(hwndMainWindow);
  narysuj(hwndMainWindow);
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
