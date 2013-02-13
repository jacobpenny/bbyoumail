import bb.cascades 1.0

Sheet {
    id: mySheet
    peekEnabled: false
    content: Page {
        Container {
            topPadding: 40
            layout: StackLayout {}
            Label {
                text: "Please enter your phone number and pin"
                layoutProperties: StackLayoutProperties {}
                horizontalAlignment: HorizontalAlignment.Center
            }
            TextField {
                id: phone_number
                objectName: "phone_number"
                inputMode: TextFieldInputMode.PhoneNumber
                hintText: "Phone Number"
                preferredWidth: 600
                layoutProperties: StackLayoutProperties {}
                horizontalAlignment: HorizontalAlignment.Center
            }
            TextField {
                id: user_pin
                objectName: "user_pin"
                inputMode: TextFieldInputMode.Password
                hintText: "PIN"
                preferredWidth: 600
                layoutProperties: StackLayoutProperties {}
                horizontalAlignment: HorizontalAlignment.Center
            }
            Button {
                objectName: "login_button"
                text: "Login"
                // onClicked: mySheet.close()
                layoutProperties: StackLayoutProperties {}
                horizontalAlignment: HorizontalAlignment.Center
            }
        }
    }
}