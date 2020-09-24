import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 480
    height: 720
    title: "Flappy Parrot"
    minimumWidth : width
    minimumHeight : height
    maximumHeight : height
    maximumWidth : width

    Item {
        id: gamewindow
        anchors.fill: parent
        Connections {
                target: backEnd
        }
        focus: true
        Keys.onSpacePressed: backEnd.but_click();

        Page1Form
        {
            settings.onClicked:
            {
                if (menu.visible)
                    menu.close()
                else
                {
                    menu.open()
                    mit1.text = "Highscore: " + backEnd.get_highScore()
                }
            }
            MouseArea {
                id: ma
                enabled: false
                anchors.fill: parent
                onClicked: backEnd.but_click();
            }
            startButton.onClicked:
            {
                ma.enabled = true
                backEnd.start()
                startButton.visible = false
                startButton.enabled = false
                settings.visible = false
                settings.enabled = false
                score.visible = true
            }
            restartButton.onClicked:
            {
                ma.enabled = false
                startButton.visible = true
                startButton.enabled = true
                startButton.focus = false
                settings.visible = true
                settings.enabled = true
                settings.focus = false
                score.visible = false
                backEnd.restart();
            }
            exit.onClicked: { Qt.callLater(Qt.quit) }

            butMit21.onClicked: { bird.source = "images/zefir.gif" }
            butMit22.onClicked: { bird.source = "images/shprot.gif" }
            butMit23.onClicked: { bird.source = "images/kesha.gif" }
            butMit24.onClicked: { bird.source = "images/khtot.gif" }
        }

    }
}
