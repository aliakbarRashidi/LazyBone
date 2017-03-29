import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import fr.grecko.LazyBone 1.0
import QtQuick.Controls.Material 2.1
import QtGraphicalEffects 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    LazyBone {
        id: lazyBone
        name: "LazyBone"
    }

    Column {
        spacing: 8
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 8
        }
        Pane {
            id: pane
            Material.elevation: 1
            property color backgroundColor: editMode ? "white" : Material.color(lazyBone.powered ? Material.Yellow : Material.Indigo)
            Material.background: backgroundColor
            Behavior on backgroundColor { ColorAnimation { easing.type: Easing.InOutQuad }}
            width: parent.width
            topPadding: editMode ? 24 : 12
            Behavior on topPadding { NumberAnimation { easing.type: Easing.InOutQuad }}
            property bool editMode: false
            onEditModeChanged: {
                if (!editMode) {
                    lazyBone.name = nameTextField.text;
                    lazyBone.hostName = hostNameTextField.text;
                    lazyBone.port = portTextField.text;
                }
            }

            implicitHeight: column.implicitHeight + topPadding + bottomPadding
            contentItem.z: 1
            RowLayout {
                width: parent.width
                spacing: 16
                Label {
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    text: lazyBone.socketState
                    color: lazyBone.socketState === Socket.ConnectedState ? Material.color(Material.Green) : Material.color(Material.Red)
                    opacity: pane.editMode ? 0 : 1
                    Behavior on opacity { NumberAnimation { easing.type: Easing.InOutQuad }}
                }
                Column {
                    z: 2
                    id: column
                    Layout.fillWidth: true
                    DirtyFloatingTextField {
                        id: nameTextField
                        width: parent.width
                        text: lazyBone.name ? lazyBone.name : (pane.editMode ? "" : "Untitled")
                        placeholderText: "Name"
                        enabled: pane.editMode
                        color: Material.primaryTextColor
                        property real backgroundOpacity: pane.editMode ? 1 : 0
                        background.opacity: backgroundOpacity
                        Behavior on backgroundOpacity { NumberAnimation { easing.type: Easing.InOutQuad }}
                        Binding {
                            target: nameTextField._placeholderItem
                            property: "opacity"
                            value: nameTextField.backgroundOpacity
                        }
                        Behavior on _placeholderY { NumberAnimation { easing.type: Easing.InOutQuad }}
                        Behavior on _placeholderFontSize { NumberAnimation { easing.type: Easing.InOutQuad }}
                    }
                    Column {
                        spacing: 12
                        topPadding: 8
                        clip: true
                        visible: height
                        height: pane.editMode ? implicitHeight : 0
                        opacity: pane.editMode ? 1 : 0
                        Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad }}
                        Behavior on opacity { NumberAnimation { easing.type: Easing.InOutQuad }}
                        width: parent.width
                        DirtyFloatingTextField {
                            id: hostNameTextField
                            width: parent.width
                            placeholderText: "Hostname"
                            text: lazyBone.hostName
                        }
                        DirtyFloatingTextField {
                            id: portTextField
                            width: parent.width
                            placeholderText: "Port"
                            text: lazyBone.port
                        }
                    }
                }

                RoundButton {
                    Material.elevation: 0
                    Layout.alignment: Qt.AlignTop | Qt.AlignRight
                    Layout.topMargin: 12 - pane.topPadding
                    onClicked: pane.editMode = !pane.editMode
                    Image {
                        id: icon
                        visible: false
                        anchors.centerIn: parent
                        property string iconSource: pane.editMode ? "check" : "settings"
                        source: "qrc:///images/icons/" + iconSource + ".svg"
                        Behavior on iconSource { FadeAnimation { target: colorOverlay }}
                    }
                    ColorOverlay {
                        id: colorOverlay
                        anchors.fill: icon
                        source: icon
                        color: Material.accent
                    }
                }
            }
            Button {
                parent: pane
                visible: enabled
                enabled: !pane.editMode
                anchors {
                    fill: parent
                    topMargin: -pane.topPadding/2
                    bottomMargin: -pane.bottomPadding/2
                }
                Material.elevation: 0
                onClicked: lazyBone.powered = !lazyBone.powered
            }
        }
    }
}
