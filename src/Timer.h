/*
 * Timer.h
 *
 *  Created on: 6 нояб. 2022 г.
 *      Author: Danila
 */

#ifndef TIMER_H_
#define TIMER_H_


struct Timer {
                    sf::Clock mC;
                    float runTime;
                    bool bPaused;

                    Timer() {
                            bPaused = false;
                            runTime = 0;
                            mC.restart();
                    }

                    void Reset() {
                            mC.restart();
                            runTime = 0;
                            bPaused = false;
                    }

                    void Start() {
                            if (bPaused) {
                                    mC.restart();
                            }
                            bPaused = false;
                    }

                    void Pause() {
                            if (!bPaused) {
                                    runTime += mC.getElapsedTime().asSeconds();
                            }
                            bPaused = true;
                    }

                    float GetElapsedSeconds() {
                            if (!bPaused) {
                                    return runTime + mC.getElapsedTime().asSeconds();
                            }
                            return runTime;
                    }
            };



#endif /* TIMER_H_ */
