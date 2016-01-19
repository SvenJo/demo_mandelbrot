#pragma once

#include <vector>
#include <functional>

#include <boost/any.hpp>

namespace easy
{
  struct EasyCommand;

  struct CommandRunner
  {
    virtual void addCommand(EasyCommand* cmd);
    std::vector<const EasyCommand*> commands;
  };

  inline void CommandRunner::addCommand(EasyCommand* cmd)
  {
    commands.push_back(cmd);
  }

  struct EasyCommand
  {
    EasyCommand(const std::string& text, std::function<void()> func)
      : func_(func)
      , text_(text)
      , enabled_(true)
      , checked_(false)
    { }

    virtual ~EasyCommand() {}

    std::string text() const { return text_; }
    boost::any native() const { return nativeinfo_; }

    bool enabled() const { return enabled_; }
    bool checked() const { return checked_; }
    void enabled(bool val) { enabled_ = val; }
    void checked(bool val) { checked_ = val; }

    virtual bool checkable() const { return false; }

    virtual void run() const { func_(); }

    template<typename T>
    void setNativeInfo(const T& nativeinfo)
    {
      nativeinfo_ = nativeinfo;
    }

  private:
    std::function<void()> func_;
    std::string text_;
    boost::any nativeinfo_; // e.g. QAction for QT of ID for Windows
    bool enabled_;
    bool checked_;
  };

  struct CheckedCommand : EasyCommand
  {
#if _MSC_VER < 1900
    // Workaround for VS2013
    CheckedCommand(const std::string& text, std::function<void()> func)
      : EasyCommand(text, func) {}
#else
    using easy::EasyCommand::EasyCommand;
#endif // _MSC_VER < 1900

    virtual void run() const override { EasyCommand::run(); const_cast<CheckedCommand*>(this)->checked(true); }
    virtual bool checkable() const override { return true; }
  };
}
