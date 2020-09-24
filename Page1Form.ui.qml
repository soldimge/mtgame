import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    width: 480
    height: 720
    property alias settings: settings
    property alias gameOverSplash: gameOverSplash
    property alias startButton: startButton
    property alias score: score
    property alias restartButton: restartButton
    property alias exit: exit
    property alias dial: dial
    property alias menu: menu
    property alias bird: bird
    property alias butMit21: butMit21
    property alias butMit22: butMit22
    property alias butMit23: butMit23
    property alias butMit24: butMit24
    property alias mit1: mit1

    Image {
        id: backimage
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: rectangle.top
        anchors.top: parent.top
        source: "images/fon3.jpg"
        fillMode: Image.Stretch
    }

    Button {
        id: startButton
        anchors.centerIn: backimage
        text: "start"
        highlighted: true
        flat: false
        font.pointSize: 32
        font.family: "Verdana"
    }


    Image {
        id: block1top
        x : 480
        width: bird.width * 1.5
        height: 200
        anchors.top: parent.top
        source: "images/block.png"
        fillMode: Image.PreserveAspectCrop
    }

    Image {
        id: block1bottom
        x : block1top.x
        width: block1top.width
        anchors.top : block1top.bottom
        anchors.topMargin: 140
        anchors.bottom: rectangle.top
        source: "images/block.png"
        fillMode: Image.PreserveAspectCrop
    }

    Image {
        id: block2top
        x : 780
        width: bird.width * 1.5
        height: 300
        anchors.top: parent.top
        source: "images/block.png"
        fillMode: Image.PreserveAspectCrop
    }

    Image {
        id: block2bottom
        x : block2top.x
        width: block2top.width
        anchors.top : block2top.bottom
        anchors.topMargin: 140
        anchors.bottom: rectangle.top
        source: "images/block.png"
        fillMode: Image.PreserveAspectCrop
    }

    Image {
        id: block3top
        x : 1080
        width: bird.width * 1.5
        height: 250
        anchors.top: parent.top
        source: "images/block.png"
        fillMode: Image.PreserveAspectCrop
    }

    Image {
        id: block3bottom
        x : block3top.x
        width: block3top.width
        anchors.top : block3top.bottom
        anchors.topMargin: 140
        anchors.bottom: rectangle.top
        source: "images/block.png"
        fillMode: Image.PreserveAspectCrop
    }

    Connections {
        target: backEnd
            onSendToQml:
            {
                bird.y = birdY
            }
            onSendToQmlMove:
            {
                block1top.x = pic1X
                block1top.height = pic1Y
                block2top.x = pic2X
                block2top.height = pic2Y
                block3top.x = pic3X
                block3top.height = pic3Y
            }
            onNewScore:
            {
                score.text = new_score
            }
            onGameOver:
            {
                dial.title = "score: " + score.text + "\nhighscore: " + backEnd.get_highScore() + newHighscore
                dial.visible = true
                dial.enabled = true
            }
            onSplash:
            {
                borderline.playing = false
                gameOverSplash.visible = !gameOverSplash.visible
                bird.rotation = 90
                bird.playing = false
            }
            onRestartQml:
            {
                dial.visible = false
                dial.enabled = false
                borderline.playing = true
                bird.playing = true
                bird.rotation = 0
            }
    }

    Rectangle {
        id: rectangle
        color: "#008b01"
        border.width: 0
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        height: width/3.3
    }

    AnimatedImage{
        id: borderline
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: rectangle.top
        height: 20
        playing: true
        speed: 0.5
        visible: true
        source: "images/TravaG.gif"
    }

    AnimatedImage{
        id: bird
        y : 350
        anchors.left: parent.left
        anchors.leftMargin: width*2.2
        width: 50
        height: 35
        playing: true
        fillMode: Image.Stretch
        speed: 2
        visible: true

        source: "images/zefir.gif"
    }


    Text {
        id: score
        anchors.horizontalCenter: parent.horizontalCenter
        y: rectangle.height/2
        color: "#ffffff"
        text: "0"
        font.bold: true
        font.family: "Verdana"
        style: Text.Outline
        font.pointSize: 32
        visible: false
    }

    Rectangle {
        id: gameOverSplash
        color: "#ffffff"
        border.width: 0
        anchors.fill: parent
        visible: false
    }

    Dialog {
            id: dial
            visible: false
            enabled: false
            modal: true
            Overlay.modal: Rectangle {
                        color: "#aacfdbe7"
                    }
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            contentItem: Rectangle {
            implicitWidth: gamewindow.width / 2
            implicitHeight: 40
            color: "#1c5066"
                Button {
                    id: restartButton
                    flat: true
                    highlighted: true
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.left: parent.horizontalCenter
                    Text {
                        text: "ok"
                        color: "#9cbdec"
                        font.bold: true
                        font.pointSize: 14
                        font.family: "Verdana"
                        anchors.centerIn: parent
                    }
                }
                Button {
                    id: exit
                    flat: true
                    highlighted: true
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.right: parent.horizontalCenter
                    onClicked: dial.visible = false
                    Text {
                        text: "exit"
                        color: "#9cbdec"
                        font.bold: true
                        font.pointSize: 14
                        font.family: "Verdana"
                        anchors.centerIn: parent
                    }
                }
            }
        }

    Menu {
        id: menu
        width: settings.width
        x: settings.x
        y: settings.y + settings.height

        MenuItem {
            id: mit1
        }
        MenuSeparator {
                    padding: 0
                    topPadding: 4
                    bottomPadding: 4
                    contentItem: Rectangle {
                    implicitWidth: 120
                    implicitHeight: 1
                    color: "#0b0d12"
                    }
        }
        MenuItem {
            id: mit2
            Button {
                id: butMit21
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: 3
                width: height*0.725
                flat: true
                highlighted: true
                Image {
                    anchors.fill: parent
                    anchors.centerIn: butMit21
                    fillMode: Image.PreserveAspectFit
                    source: "images/zefir.gif"
                    scale: 0.75
                }
            }
            Button {
                id: butMit22
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: butMit21.right
                anchors.leftMargin: 3
                width: height*0.725
                flat: true
                highlighted: true
                Image {
                    anchors.fill: parent
                    anchors.centerIn: butMit22
                    fillMode: Image.PreserveAspectFit
                    source: "images/shprot.gif"
                    scale: 0.75
                }
            }
            Button {
                id: butMit23
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: butMit22.right
                anchors.leftMargin: 3
                width: height*0.725
                flat: true
                highlighted: true
                Image {
                    anchors.fill: parent
                    anchors.centerIn: butMit23
                    fillMode: Image.PreserveAspectFit
                    source: "images/kesha.gif"
                    scale: 0.75
                }
            }
            Button {
                id: butMit24
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: butMit23.right
                anchors.leftMargin: 3
                width: height*0.725
                flat: true
                highlighted: true
                Image {
                    anchors.fill: parent
                    anchors.centerIn: butMit24
                    fillMode: Image.PreserveAspectFit
                    source: "images/khtot.gif"
                    scale: 0.75
                }
            }
        }
    }
    Button {
        id: settings
        anchors.left: startButton.left
        anchors.right: startButton.right
        anchors.top: startButton.bottom
        Text {
            color: "#1c5066"
            text: "settings"
            font.pointSize: 18
            font.family: "Verdana"
            anchors.centerIn: parent
        }
        highlighted: true
        flat: false
    }
}

