// Tabbed Pane project template
import bb.cascades 1.0

TabbedPane {
    showTabsOnActionBar: true
    Tab {
        title: qsTr("Messages")
        Page {
            id: tab1
            actions: [
                ActionItem {
                    title: qsTr("Refresh")
                    onTriggered: {
                    }
                },
                ActionItem {
                    title: qsTr("Dial Voicemail")
                    onTriggered: {
                    }
                },
                ActionItem {
                    title: qsTr("Search")
                    onTriggered: {
                    }
                },
                ActionItem {
                    title: qsTr("Preferences")
                    onTriggered: {
                    }
                },
                ActionItem {
                    title: qsTr("Help")
                    onTriggered: {
                    }
                }
            ]
            Container {
                Label {
                    text: qsTr("Tab 1 title")
                    horizontalAlignment: HorizontalAlignment.Center
                    textStyle {
                        base: SystemDefaults.TextStyles.TitleText
                    }
                }
            }
        }
    }
    Tab {
        title: qsTr("Hang Ups")
        Page {
            id: tab2
            actions: [
                ActionItem {
                    title: qsTr("Refresh")
                    onTriggered: {
                    }
                },
                ActionItem {
                    title: qsTr("Preferences")
                    onTriggered: {
                    }
                },
                ActionItem {
                    title: qsTr("Help")
                    onTriggered: {
                    }
                }
            ]
            Container {
                Label {
                    text: qsTr("Tab 2 title")
                    horizontalAlignment: HorizontalAlignment.Center
                    textStyle {
                        base: SystemDefaults.TextStyles.TitleText
                    }
                }
            }
        }
    }
    Tab {
        title: qsTr("Greetings")
        Page {
            id: tab3
            actions: [
                ActionItem {
                    title: qsTr("Special Callers")
                    onTriggered: {
                    }
                },
                ActionItem {
                    title: qsTr("Preferences")
                    onTriggered: {
                    }
                },
                ActionItem {
                    title: qsTr("Help")
                    onTriggered: {
                    }
                }
            ]
            Container {
                Label {
                    text: qsTr("Tab 3 title")
                    horizontalAlignment: HorizontalAlignment.Center
                    textStyle {
                        base: SystemDefaults.TextStyles.TitleText
                    }
                }
            }
        }
    }
    Tab {
        title: qsTr("People")
        Page {
            id: tab4
            actions: [
                ActionItem {
                    title: qsTr("Ditch Caller")
                    onTriggered: {
                    }
                },
                ActionItem {
                    title: qsTr("Preferences")
                    onTriggered: {
                    }
                },
                ActionItem {
                    title: qsTr("Help")
                    onTriggered: {
                    }
                }
            ]
            Container {
                Label {
                    text: qsTr("Tab 3 title")
                    horizontalAlignment: HorizontalAlignment.Center
                    textStyle {
                        base: SystemDefaults.TextStyles.TitleText
                    }
                }
            }
        }
    }
    onCreationCompleted: {
        // this slot is called when declarative scene is created
        // write post creation initialization here
        console.log("TabbedPane - onCreationCompleted()")
        
        // enable layout to adapt to the device rotation
        // don't forget to enable screen rotation in bar-bescriptor.xml (Application->Orientation->Auto-orient)
        OrientationSupport.supportedDisplayOrientation = SupportedDisplayOrientation.All;
    }
}
