import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 1000
    height: 700
    title: "flowTrack Local (MVP)"

    Column {
        anchors.fill: parent
        spacing: 10
        padding: 12

        Text { text: "flowTrack (Local)"; font.pixelSize: 24 }

        Button {
            text: "Refresh Queue"
            onClicked: {
                // trigger processor to read queue via minimal approach:
                // for demo we restart app or call into main via registered context property later
                console.log("Please restart app to reprocess queue for MVP");
            }
        }
        Rectangle { color: "#eee"; height: 1; anchors.left: parent.left; anchors.right: parent.right }

        // For MVP we simply show static text: DB listing UI requires exposing a model via context properties
        Text { text: "Commits are saved to local SQLite. Implement ListView model later." }
    }
}
