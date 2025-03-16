#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QSoundEffect>

#ifdef false
#include <QMediaPlayer>
#include <QAudioOutput>
#endif

class SoundManager : public QObject
{
    Q_OBJECT

public:
    explicit SoundManager(QObject *parent = nullptr);

public slots:
    void playButtonClickSound();

    void playCardFailSound();

    void playCardTurnSound();

    void playTakeCardSound();

private:
    QSoundEffect *m_soundEffect;

#ifdef false
    QMediaPlayer *m_mediaPlayer;

    QAudioOutput *m_audioOutput;
#endif
};

#endif // SOUNDMANAGER_H
