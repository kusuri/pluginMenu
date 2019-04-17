In general, juce::Combobox consists of a juce::Label and a juce::PopupMenu. 
There are several ways to show a popup menu either as a modal window or not. 
The main problem with combobox is that although the popup is NOT shown as modal the parent component is not set up explicitely and as a result it is a nullptr.
When the parent is null then popupmenu is a new window on desktop (NOT a modal window!) because `addToDesktop` is called.
However, if the parent component is not null then the popup menu 

To sum up in order to solve this problem create a Component (Label, Button or whatever suits you best) and when its pressed create a `juce::PopupMenu` component and set `PluginEditor` its parent component (I wouldn't suggest to use the parent of the target component because sometimes, depending on the parent bounds, the popupmenu might not be visible).


```c++
void MenuTestAudioProcessorEditor::showPopupMenu()
{
    PopupMenu menu;
    menu.addItem(1, "Menu Text1");
    menu.addItem(2, "Menu Text2");

    // with `showMenuAsync` the popup won't be a modal window
    // also when parent component is NOT nullptr then if menu is shown and the user moves the plugin window,
    // the menu will still be visible but inside the plugin window.
    menu.showMenuAsync (PopupMenu::Options().withParentComponent(this)
                                            .withTargetComponent (&buttonTriggerMenu)
                                            .withItemThatMustBeVisible (1) // change this depending on the current menu state
                                            .withMinimumWidth (buttonTriggerMenu.getWidth())
                                            .withMaximumNumColumns (1)
                                            .withStandardItemHeight (buttonTriggerMenu.getHeight()),
                        ModalCallbackFunction::create([this](int result){this->menuCallback(result);}));
}
```
