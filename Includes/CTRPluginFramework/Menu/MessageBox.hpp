#ifndef CTRPLUGINFRAMEWORK_MESSAGEBOX_HPP
#define CTRPLUGINFRAMEWORK_MESSAGEBOX_HPP

#include <memory>
#include <string>

namespace CTRPluginFramework
{
    enum class DialogType
    {
        DialogOk,
        DialogOkCancel,
        DialogYesNo
    };

    class MessageBoxImpl;
    class MessageBox
    {
    public:
        MessageBox(const std::string &title, const std::string &message, DialogType dialogType = DialogType::DialogOk);
        MessageBox(const std::string &message, DialogType dialogType = DialogType::DialogOk);
        ~MessageBox(void);

        // Display the Message Box and wait for the user input
        // Return:
        // True if user selected Yes / Ok
        // False is user selected No / Cancel
        bool operator()(void) const;
    private:
        std::unique_ptr<MessageBoxImpl>  _messageBox;
    };
}

#endif
