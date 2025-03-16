#include "soundmanager.h"

#include <QDebug>
#include <QAudioDevice>

SoundManager::SoundManager(QObject *parent) : QObject(parent)
{
    m_soundEffect = new QSoundEffect(this);
    m_soundEffect->setVolume(1.0);

#ifdef false
    m_mediaPlayer = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_audioOutput->setVolume(1.0); // Set volume to maximum (1.0)
    m_mediaPlayer->setAudioOutput(m_audioOutput);

    // Connect to the errorOccurred signal to debug issues
    connect(m_mediaPlayer, &QMediaPlayer::errorOccurred, this, [](QMediaPlayer::Error error, const QString &errorString) {
        qDebug() << "MediaPlayer error:" << errorString;
    });

    // Connect to the mediaStatusChanged signal to debug media loading
    connect(m_mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, [](QMediaPlayer::MediaStatus status) {
        qDebug() << "MediaPlayer status:" << status;
    });
#endif
}

void SoundManager::playButtonClickSound()
{
    m_soundEffect->setSource(QUrl::fromLocalFile(":/sounds/button-click.wav"));
    m_soundEffect->play();
    qDebug() << "Available audio devices:" << QAudioDevice{}.description();

#ifdef false
    m_mediaPlayer->setSource(QUrl::fromLocalFile(":/sounds/button-click.wav"));
    m_mediaPlayer->play();
#endif
}

void SoundManager::playCardFailSound()
{
    m_soundEffect->setSource(QUrl::fromLocalFile(":/sounds/card-fail.wav"));
    m_soundEffect->play();

#ifdef false
    m_mediaPlayer->setSource(QUrl::fromLocalFile(":/sounds/card-fail.wav"));
    m_mediaPlayer->play();
#endif
}

void SoundManager::playCardTurnSound()
{
    m_soundEffect->setSource(QUrl::fromLocalFile(":/sounds/card-turn.wav"));
    m_soundEffect->play();

#ifdef false
    m_mediaPlayer->setSource(QUrl::fromLocalFile(":/sounds/card-turn.wav"));
    m_mediaPlayer->play();
#endif
}

void SoundManager::playTakeCardSound()
{
    m_soundEffect->setSource(QUrl::fromLocalFile(":/sounds/take-card.wav"));
    m_soundEffect->play();

#ifdef false
    m_mediaPlayer->setSource(QUrl::fromLocalFile(":/sounds/take-card.wav"));
    m_mediaPlayer->play();
#endif
}
