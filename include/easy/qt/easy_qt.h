#pragma once

#include <QMenu>

namespace easy
{
  namespace qt
  {
    struct EasyPopupMenu : QMenu
    {
      EasyPopupMenu(QWidget* parent) : QMenu(parent) {}

      void AppendSeperator() { addSeparator(); }

      void AppendCommand(const EasyCommand* cmd)
      {
        assert(cmd);
        auto* action = boost::any_cast<QAction*>(cmd->native());
        assert(action);
        action->setChecked(cmd->checked());
        action->setEnabled(cmd->enabled());
        addAction(action);
      }
    };

  }
}
