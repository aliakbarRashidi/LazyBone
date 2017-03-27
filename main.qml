import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import fr.grecko.LazyBone 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    LazyBone {
        id: lb
        hostName: "192.168.0.14"
        property bool isOn: false
        powered: isOn
    }

    Button {
        anchors.centerIn: parent
        text: "Toggle"
        onClicked: lb.isOn = !lb.isOn
    }
}
