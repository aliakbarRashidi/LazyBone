import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1

TextField {
    id: root
    property bool _showPlaceholder: !length && !preeditText && (!activeFocus || horizontalAlignment !== Qt.AlignHCenter)
    property Item _placeholderItem: {
        for (var i = 0; i < children.length; ++i) {
            if (children[i].toString().indexOf("QQuickText") === 0)
                return children[i];
        }
    }
    property real _placeholderY: _showPlaceholder ? topPadding : -12
    property real _placeholderFontSize: _showPlaceholder ? font.pixelSize : 12
    Behavior on _placeholderY { NumberAnimation { easing.type: Easing.InOutQuad }}
    Behavior on _placeholderFontSize { NumberAnimation { easing.type: Easing.InOutQuad }}
    Binding {
        target: _placeholderItem
        property: "visible"
        value: true
    }
    Binding {
        target: _placeholderItem
        property: "y"
        value: _placeholderY
    }
    on_PlaceholderItemChanged: {
        _placeholderItem.font.pixelSize = Qt.binding(function() { return _placeholderFontSize; });
    }
}
