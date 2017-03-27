import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import fr.grecko.LazyBone 1.0
import QtQuick.Controls.Material 2.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    LazyBone {
        id: lb
        hostName: "192.168.0.14"
    }

    Button {
        anchors.centerIn: parent
        Material.background: lb.powered ? Material.Yellow : Material.Indigo
        text: "Toggle"
        onClicked: lb.powered = !lb.powered
    }
}
