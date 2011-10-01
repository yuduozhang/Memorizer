/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "Mainwindow.h"
#include "Memorizer.h"

//! [0]
Mainwindow::Mainwindow()
{
    // Now we make it as simple as possible, so only one Dictionary
    // exists (Japanese). We will make it handle to choose a dictionary.

    DICTIONARY dict("Japanese");
    dict.open();




    createKeyForm();
    createContentForm();

    addWordButton = new QPushButton(tr("Add Word"));
    reviewButton = new QPushButton(tr("Review: 21 words to review"));


    //connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    //connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;


    mainLayout->addWidget(keyGroupBox);
    mainLayout->addWidget(contentGroupBox);
    mainLayout->addWidget(addWordButton);
    mainLayout->addWidget(reviewButton);


    setLayout(mainLayout);

    setWindowTitle(tr("Memorizer 0.1"));
}


void Mainwindow::createKeyForm()
{
    keyGroupBox = new QGroupBox(tr("Key"));

    QGridLayout *layout = new QGridLayout;

    keyEditor = new QTextEdit;
    keyEditor->setPlainText(tr("This is where the key goes "));
    layout->addWidget(keyEditor);


    keyGroupBox->setLayout(layout);
}

void Mainwindow::createContentForm()
{
    contentGroupBox = new QGroupBox(tr("Content"));

    QGridLayout *layout = new QGridLayout;

    contentEditor = new QTextEdit;
    contentEditor->setPlainText(tr("This is where the content goes "));
    layout->addWidget(contentEditor);


    contentGroupBox->setLayout(layout);
}


void Mainwindow::addWord(){

}

void reviewMode();

