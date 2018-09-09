
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <SFML/Audio.hpp>

using namespace std;

using namespace sf;

struct Point
{
    int x, y;
};

int main()
{
    /*
    ~~~~~~~~~ Game States ~~~~~~~~~
    -1= Intro
    0 = Main menu
    1 = GameLoop
    2 = Game Over
    3 = Help
    4 = HighScore
    */
    int gameState=-1;
    bool startNow=true, startNow2=false, menuStart=true, overStart=true, music=true, bonusStart=true, bonusBool=false, increaseLevel=false;
    int fps=10, foodX, foodY, score=0, snakeSize=3, foodCount=0, highscore=0, bonus=600, bonusTimer;
    float keyPresstimer, delay=.1, menuTimer=0.0f, extraTimer=0.0f;
    int x=32, y=32; // Snake Head Position
    int startTextPosX, levelTextPosX, instructTextPosX, highscoreTextPosX, exitTextPosX;
    unsigned int menuSelection=0;
    Texture Tbg, TsnakePng, TheadUp, TheadDown, TheadLeft, TheadRight, TbodyHorr, TbodyVert, TtailUp, TtailDown, TtailLeft, TtailRight, TleftUp,
            TleftDown, TrightUp, TrightDown, Tfood, TbonusFood, ThaaUp, ThaaDown, ThaaLeft, ThaaRight, TmenuBG, TsnakeTree, TsnakeCute, TsnakeBig,
            TmenuTitle, ToverBG, ThelpBG, TbeatBG, ThighBG, Tintro;
    Point point[500];
    Font gothic, grobold;
    Clock keyPressclock, menuClock, extraClock, bonusClock;
    Music menuMusic, gameMusic, overMusic;
    SoundBuffer SBeat, SBdie, SBselect, SBselected, SBbonusAppear, SBbonusTime;
    Color selected(85, 104, 42, 200), notSelected(121, 130, 59, 100), beat(200, 20, 20);
    srand(time(NULL));



    RenderWindow win(VideoMode(960, 600), "Snake Mania");
    win.setFramerateLimit(20);

    /*
    ~~~~~~~~ DIRECTIONS (dir) ~~~~~~~~
    # 0 = UP
    # 1 = RIGHT
    # 2 = DOWN
    # 3 = LEFT
    */

    int dir=1;

    Tbg.loadFromFile		("images/bgS.png");
    TheadRight.loadFromFile ("images/16/headRight.png");
    TheadLeft.loadFromFile  ("images/16/headLeft.png");
    TheadUp.loadFromFile    ("images/16/headUp.png");
    TheadDown.loadFromFile  ("images/16/headDown.png");
    TbodyHorr.loadFromFile  ("images/16/bodyHorr.png");
    TbodyVert.loadFromFile  ("images/16/bodyVert.png");
    TheadRight.loadFromFile ("images/16/headRight.png");
    TtailUp.loadFromFile    ("images/16/tailUp.png");
    TtailDown.loadFromFile  ("images/16/tailDown.png");
    TtailRight.loadFromFile ("images/16/tailRight.png");
    TtailLeft.loadFromFile  ("images/16/tailLeft.png");
    TleftUp.loadFromFile    ("images/16/leftUp.png");
    TleftDown.loadFromFile  ("images/16/leftDown.png");
    TrightUp.loadFromFile   ("images/16/rightUp.png");
    TrightDown.loadFromFile ("images/16/rightDown.png");
    Tfood.loadFromFile      ("images/16/food.png");
    ThaaUp.loadFromFile     ("images/16/haaUp.png");
    ThaaDown.loadFromFile   ("images/16/haaDown.png");
    ThaaLeft.loadFromFile   ("images/16/haaLeft.png");
    ThaaRight.loadFromFile  ("images/16/haaRight.png");
    TbonusFood.loadFromFile ("images/bonusFood.png");

    TmenuBG.loadFromFile    ("images/menu/bg.png");
    TsnakeTree.loadFromFile ("images/menu/snakeTree.png");
    TsnakeCute.loadFromFile ("images/menu/snakeCute.png");
    TsnakeBig.loadFromFile  ("images/menu/snakeBig.png");
    TmenuTitle.loadFromFile ("images/menu/title.png");

    ToverBG.loadFromFile    ("images/menu/overBG.png");
    TbeatBG.loadFromFile    ("images/menu/overBeatBG.png");
    ThelpBG.loadFromFile    ("images/help.png");
    ThighBG.loadFromFile    ("images/highBG.png");
    Tintro.loadFromFile     ("images/intro.png");

    gothic.loadFromFile     ("fonts/gothic.ttf");
    grobold.loadFromFile    ("fonts/grobold.ttf");

    SBeat.loadFromFile      ("audios/eat.ogg");
    SBdie.loadFromFile      ("audios/die.ogg");
    SBselect.loadFromFile   ("audios/select.ogg");
    SBselected.loadFromFile ("audios/selected.ogg");
    SBbonusAppear.loadFromFile("audios/pop.ogg");
    SBbonusTime.loadFromFile("audios/bonusTime.ogg");

    menuMusic.openFromFile  ("audios/intro.ogg");
    gameMusic.openFromFile  ("audios/game.ogg");
    overMusic.openFromFile  ("audios/over.ogg");


    gameMusic.setVolume(45);
    menuMusic.setVolume(60);
    overMusic.setVolume(60);


    Sprite  head(TheadRight), tail(TtailRight), body[500], food(Tfood), menuBG(TmenuBG), snakeTree(TsnakeTree), snakeCute(TsnakeCute),
            snakeBig(TsnakeBig), menuTitle(TmenuTitle), overBG(ToverBG), helpBG(ThelpBG), highBG(ThighBG), intro(Tintro);
    Sprite bgspr(Tbg);

    Sound eat(SBeat), dieS(SBdie), bonusAppear(SBbonusAppear), bonusTime(SBbonusTime), selectS(SBselect), selectedS(SBselected);

    int sBigY=240, sTreeX=-400, mTitleY=-200, sCuteX=260;
    snakeBig.setPosition(0, sBigY);
    snakeTree.setPosition(sTreeX, 0);
    menuTitle.setPosition(0, mTitleY);
    snakeCute.setPosition(sCuteX, 0);

    Event ev;
    while(win.isOpen())
    {
        while(win.pollEvent(ev))
        {
            if(ev.type==Event::Closed)
                win.close();
        }

        /// INTRO

        if(gameState==-1){
            win.clear();
            win.draw(intro);
            if(Keyboard::isKeyPressed(Keyboard::Enter)) gameState=0, menuClock.restart();
        }

        /// MENU

        if(gameState==0){
            win.clear();
            win.draw(menuBG);
            if(menuStart){
                freopen("GAME_DATA.DAT", "r", stdin);
                cin>>highscore;
                fclose(stdin);

                overMusic.stop();
                if(music) menuMusic.play();
                menuStart=false;
                menuMusic.setLoop(true);
                startTextPosX=965;
                instructTextPosX=965;
                highscoreTextPosX=1070;
                exitTextPosX=1215;
            }
            menuTimer=menuClock.getElapsedTime().asSeconds();
            if(Keyboard::isKeyPressed(Keyboard::M) && menuTimer>.5){
                if(music && menuMusic.Playing) menuMusic.pause(), music=false;
                else menuMusic.play(), music=true;
                menuClock.restart();
            }

            if(sBigY>0) sBigY-=12;
            if(sTreeX<0) sTreeX+=20;
            if(mTitleY<0) mTitleY+=10;
            if(sCuteX>0) sCuteX-=13;

            snakeBig.setPosition        (0, sBigY);
            snakeTree.setPosition       (sTreeX, 0);
            menuTitle.setPosition       (0, mTitleY);
            snakeCute.setPosition       (sCuteX, 0);

            Text startText              ("START", grobold, 40);
            Text instructText           ("INSTRUCTIONS", grobold, 40);
            Text highscoreText          ("HIGHSCORE", grobold, 40);
            Text exitText               ("EXIT", grobold, 40);

            if(startTextPosX>565)       startTextPosX-=40;
            if(instructTextPosX>485)    instructTextPosX-=40;
            if(highscoreTextPosX>510)   highscoreTextPosX-=40;
            if(exitTextPosX>575)        exitTextPosX-=40;

            startText.setPosition       (startTextPosX, 140);
            instructText.setPosition    (instructTextPosX, 220);
            highscoreText.setPosition   (highscoreTextPosX, 300);
            exitText.setPosition        (exitTextPosX, 380);

            startText.setFillColor          (notSelected);
            instructText.setFillColor       (notSelected);
            highscoreText.setFillColor      (notSelected);
            exitText.setFillColor           (notSelected);

            switch(menuSelection%4){
            case 0:
                startText.setFillColor(selected);
                break;
            case 1:
                instructText.setFillColor(selected);
                break;
            case 2:
                highscoreText.setFillColor(selected);
                break;
            case 3:
                exitText.setFillColor(selected);
                break;
            }

            if(Keyboard::isKeyPressed(Keyboard::Down)   && menuTimer>.2) menuSelection++, menuClock.restart(), selectS.play();
            if(Keyboard::isKeyPressed(Keyboard::Up)     && menuTimer>.2) menuSelection--, menuClock.restart(), selectS.play();
            if(Keyboard::isKeyPressed(Keyboard::Enter)  && menuTimer>.2){
                extraClock.restart();
                selectedS.play();
                switch(menuSelection%4){
                case 0:
                    gameState=1;
                    menuMusic.stop();
                    break;
                case 1:
                    gameState=3;
                    break;
                case 2:
                    gameState=4;
                    break;
                case 3:
                    win.close();
                    break;
                }

            }

            win.draw(startText);
            win.draw(instructText);
            win.draw(highscoreText);
            win.draw(exitText);
            win.draw(snakeBig);
            win.draw(snakeTree);
            win.draw(snakeCute);
            win.draw(menuTitle);
        }

        /// GAME OVER

        if(gameState==2){
            win.clear();
            if(overStart){

                freopen("GAME_DATA.DAT", "w", stdout);
                if(highscore<=score) cout<<score<<endl;
                else cout<<highscore<<endl;
                fclose(stdout);

                gameMusic.stop();
                if(music) overMusic.play();
                overStart=false;
                overMusic.setLoop(true);
                win.setFramerateLimit(20);
            }
            menuTimer=menuClock.getElapsedTime().asSeconds();
            if(Keyboard::isKeyPressed(Keyboard::M) && menuTimer>.5){
                if(music && overMusic.Playing) overMusic.pause(), music=false;
                else overMusic.play(), music=true;
                menuClock.restart();
            }
            menuMusic.setVolume(100);
            char overScore[25];
            sprintf(overScore, "Your Score: %d", score);
            Text overScoreText(overScore, gothic, 40);
            overScoreText.setPosition(340,220);
            overScoreText.setFillColor(Color::Yellow);
            if(score>=highscore) overBG.setTexture(TbeatBG);
            else overBG.setTexture(ToverBG);
            win.draw(overBG);
            win.draw(overScoreText);
            if(Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::BackSpace)){
                score=0;
                snakeSize=3;
                gameState=0;
                startNow=true;
                menuStart=true;
                sBigY=240;
                sTreeX=-400;
                mTitleY=-200;
                sCuteX=260;
                menuClock.restart();
            }
        }

        /// HELP PAGE

        if(gameState==3){
            win.clear();
            win.draw(helpBG);
            extraTimer=extraClock.getElapsedTime().asSeconds();
            if(Keyboard::isKeyPressed(Keyboard::Enter) && extraTimer>.2) gameState=0, extraClock.restart();
            if(Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::BackSpace)) gameState=0;
        }

        /// HIGHSCORE PAGE

        if(gameState==4){
            win.clear();
            win.draw(highBG);
            char printHigh[20];
            sprintf(printHigh, "Highscore : %d", highscore);
            Text textHigh(printHigh, grobold, 40);
            textHigh.setPosition(350, 280);
            textHigh.setColor(beat);
            win.draw(textHigh);
            Text backText("BACK", grobold, 40);
            backText.setPosition(800, 450);
            backText.setColor(selected);
            win.draw(backText);
            extraTimer=extraClock.getElapsedTime().asSeconds();
            if(Keyboard::isKeyPressed(Keyboard::Enter) && extraTimer>.2) gameState=0, extraClock.restart();
            if(Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::BackSpace)) gameState=0;
        }


        /// GAME LOOP

        if(gameState==1){
            win.clear();
            win.draw(bgspr);

            int angX, angY, ang, f=0;

            /*
            ~~~~~~~~Angles~~~~~~~~
            # 0 = Right-Up
            # 1 = Right-Down
            # 2 = Left-Up
            # 3 = Left-Down
            */

            if(startNow){
                fps=10;
                win.setFramerateLimit(fps);
                if(music) gameMusic.play();
                gameMusic.setLoop(true);
                point[0].x = 32;
                point[0].y = 32;
                dir=1;
                x=32;
                y=32;
                tail.setPosition(16, 32);
                body[1].setTexture(TbodyHorr);
                body[1].setPosition(32, 32);
                win.draw(tail);
                foodX=(rand()%928)+16;
                foodY=(rand()%528)+16;
                foodX-=(foodX%16);
                foodY-=(foodY%16);
                food.setPosition(foodX, foodY);
                foodCount=0;
                startNow=false;
                startNow2=false;
                overStart=true;
                increaseLevel=false;
            }

            menuTimer=menuClock.getElapsedTime().asSeconds();
            if(Keyboard::isKeyPressed(Keyboard::M) && menuTimer>.5){
                if(music && gameMusic.Playing) gameMusic.pause(), music=false;
                else gameMusic.play(), music=true;
                menuClock.restart();
            }
            keyPresstimer=keyPressclock.getElapsedTime().asSeconds();
            if((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))     && dir!=2 && dir!=0 && keyPresstimer>.05)   dir=0, keyPressclock.restart();
            if((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))  && dir!=3 && dir!=1 && keyPresstimer>.05)   dir=1, keyPressclock.restart();
            if((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))   && dir!=0 && dir!=2 && keyPresstimer>.05)   dir=2, keyPressclock.restart();
            if((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))   && dir!=1 && dir!=3 && keyPresstimer>.05)   dir=3, keyPressclock.restart();

            for(int i=snakeSize-1; i>=1; i--){
                point[i].x=point[i-1].x;
                point[i].y=point[i-1].y;

                if(point[i].y==point[i-1].y && point[i].y==point[i+1].y) body[i].setTexture(TbodyHorr);
                if(point[i].x==point[i-1].x && point[i].x==point[i+1].x) body[i].setTexture(TbodyVert);

            }

            if(dir==0){
                head.setTexture(TheadUp);
                y-=16;
                if(x==foodX && y<(foodY+48) && y>=foodY) head.setTexture(ThaaUp);
            }
            if(dir==1){
                head.setTexture(TheadRight);
                x+=16;
                if(y==foodY && x>(foodX-48) && x<=foodX) head.setTexture(ThaaRight);
            }
            if(dir==2){
                head.setTexture(TheadDown);
                y+=16;
                if(x==foodX && y>(foodY-48) && y<=foodY) head.setTexture(ThaaDown);
            }
            if(dir==3){
                head.setTexture(TheadLeft);
                x-=16;
                if(y==foodY && x<(foodX+48) && x>=foodX) head.setTexture(ThaaLeft);
            }
            head.setPosition(x, y);

            point[0].x=x;
            point[0].y=y;

            for(int i=1; i<snakeSize-1; i++){
                if((point[i].y>point[i-1].y && point[i].x==point[i-1].x && point[i].x>point[i+1].x && point[i].y==point[i+1].y)
                || (point[i].y==point[i-1].y && point[i].x>point[i-1].x && point[i].x==point[i+1].x && point[i].y>point[i+1].y)) body[i].setTexture(TrightUp);

                if((point[i].y>point[i-1].y && point[i].x==point[i-1].x && point[i].x<point[i+1].x && point[i].y==point[i+1].y)
                || (point[i].y==point[i-1].y && point[i].x<point[i-1].x && point[i].x==point[i+1].x && point[i].y>point[i+1].y)) body[i].setTexture(TleftUp);

                if((point[i].y<point[i-1].y && point[i].x==point[i-1].x && point[i].x>point[i+1].x && point[i].y==point[i+1].y)
                || (point[i].y==point[i-1].y && point[i].x>point[i-1].x && point[i].x==point[i+1].x && point[i].y<point[i+1].y)) body[i].setTexture(TrightDown);

                if((point[i].y<point[i-1].y && point[i].x==point[i-1].x && point[i].x<point[i+1].x && point[i].y==point[i+1].y)
                || (point[i].y==point[i-1].y && point[i].x<point[i-1].x && point[i].x==point[i+1].x && point[i].y<point[i+1].y)) body[i].setTexture(TleftDown);

                if(i<snakeSize-1){
                    body[i].setPosition(point[i].x,point[i].y);
                    win.draw(body[i]);
                }
            }

            if(point[snakeSize-2].x>point[snakeSize-1].x) tail.setTexture(TtailRight);
            if(point[snakeSize-2].y>point[snakeSize-1].y) tail.setTexture(TtailDown);
            if(point[snakeSize-2].x<point[snakeSize-1].x) tail.setTexture(TtailLeft);
            if(point[snakeSize-2].y<point[snakeSize-1].y) tail.setTexture(TtailUp);

            if(startNow2) tail.setPosition(point[snakeSize-1].x,point[snakeSize-1].y);
            startNow2=true;

            if(foodCount%10==0 && increaseLevel) fps++, increaseLevel=false, win.setFramerateLimit(fps);

            if(foodCount%5==0 && foodCount!=0 && bonusBool){
                if(bonusStart){
                    food.setTexture(TbonusFood);
                    bonusAppear.play();
                    bonusTime.play();
                    bonusStart=false;
                    bonus=fps*50;
                }
                if(bonus>1){
                    if(x==foodX && y==foodY){
                        bonusAppear.play();
                        bonusTime.stop();
                        foodX=(rand()%928)+16, foodY=(rand()%528)+16;
                        foodX-=(foodX%16);
                        foodY-=(foodY%16);
                        food.setPosition(foodX, foodY);
                        snakeSize++;
                        foodCount++;
                        score+=bonus;
                        increaseLevel=true;
                    }
                    char hurryUp[20];
                    sprintf(hurryUp, "Hurry Up : %d", bonus);
                    Text hurryUpText(hurryUp, gothic, 22);
                    hurryUpText.setFillColor(beat);
                    hurryUpText.setPosition(380, 565);
                    win.draw(hurryUpText);
                    bonus-=10;
                }
                if(bonus==0) bonusBool=false, food.setTexture(Tfood), bonusAppear.play();
            }
            else {
                food.setTexture(Tfood);
                bonusStart=true;
                if(x==foodX && y==foodY){
                    eat.play();
                    score+=(fps-9);
                    foodX=(rand()%928)+16, foodY=(rand()%528)+16;
                    foodX-=(foodX%16);
                    foodY-=(foodY%16);
                    food.setPosition(foodX, foodY);
                    snakeSize++;
                    foodCount++;
                    bonusBool=true;
                    increaseLevel=true;
                }
            }

            for(int i=1; i<snakeSize-1; i++){
                while(foodX==point[i].x && foodY==point[i].y){
                    foodX=(rand()%928)+16, foodY=(rand()%528)+16;
                    foodX-=(foodX%16);
                    foodY-=(foodY%16);
                    food.setPosition(foodX, foodY);
                }
            }

            char scorePrint[20], highscorePrint[20];
            sprintf(scorePrint, "Score: %d", score);
            sprintf(highscorePrint, "Best Score: %d", highscore);
            Text scoreText(scorePrint, gothic, 22);
            Text highscoreText(highscorePrint, gothic, 22);
            scoreText.setPosition(10, 565);
            highscoreText.setPosition(780, 565);
            scoreText.setFillColor(beat);
            highscoreText.setFillColor(beat);

            for(int i=1; i<snakeSize; i++){
                if(x==point[i].x && y==point[i].y){
                    dieS.play();
                    gameState=2;
                }
             }

             if(highscore<=score){
                highscoreText.setFillColor(Color::Red);
                highscoreText.setPosition(800,565);
                highscore=score;
             }

            win.draw(scoreText);
            win.draw(highscoreText);
            win.draw(food);
            win.draw(head);
            win.draw(tail);
            if(x>929 || x<15 || y>529 || y<15){
                dieS.play();
                gameState=2;
            }
        }
        win.display();
    }
}

