#pragma once

#include "../command.h"

namespace easy
{
  namespace mfc
  {
    struct EasyPopupMenu : CMenu
    {
      EasyPopupMenu()
      {
        CreatePopupMenu();
      }
      void AppendSeperator() { AppendMenu(MF_SEPARATOR); }

      void AppendCommand(const EasyCommand* cmd)
      {
        assert(cmd);

        UINT flag = MF_STRING;
        flag |= cmd->checked() ? MF_CHECKED : MF_UNCHECKED;
        flag |= cmd->enabled() ? MF_ENABLED : MF_DISABLED;
        std::string text = cmd->text();
        std::wstring wtext(text.begin(), text.end());
        AppendMenu(flag, boost::any_cast<UINT>(cmd->native()), wtext.c_str());
      }

      void execute(int x, int y, CWnd* parent)
      {
        TrackPopupMenu(TPM_LEFTBUTTON, x, y, parent);
      }
    };

    enum ID_RANGE
    {
      ID_START = 4000,
      ID_END = 5000,
    };

    template<typename WND>
    struct EasyWnd : WND
    {
      using super = WND;

      virtual int nextId()
      {
        return ++nextid_;
      }

    private:
      virtual void OnViewCommand(UINT id) = 0;
      int nextid_ = ID_START;

      DECLARE_MESSAGE_MAP()
    };

    BEGIN_TEMPLATE_MESSAGE_MAP(EasyWnd, WND, super)
      ON_COMMAND_RANGE(ID_START, ID_END, OnViewCommand)
    END_MESSAGE_MAP();
  }
}
