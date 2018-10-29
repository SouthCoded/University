import { Component } from '@angular/core';
import {NavController, NavParams } from 'ionic-angular';

import { LoginPasswordPage } from '../login-password/login-password'


import { GlobalVariables } from '../../providers/globalvariables'

/**
 * Generated class for the LoginPage page.
 *
 * See https://ionicframework.com/docs/components/#navigation for more info on
 * Ionic pages and navigation.
 */

var a1Link = 'false';
var a2Link = 'true';
var b1Link = 'false';
var b2Link = 'true';
var c1Link = 'false';
var c2Link = 'true';
var d1Link = 'false';
var d2Link = 'false';
var e1Link = 'false';
var e2Link = 'true';

@Component({ selector: 'page-login', templateUrl: 'login.html',})
export class LoginPage {

  constructor(public navCtrl: NavController, public navParams: NavParams, public globalVars : GlobalVariables) {
    globalVars.loginState = false;
    globalVars.serverAddress = 'http://localhost:8080';
  }
  

  //Set the value passed into method setA1 to a1link so that other methods, such as setA2 can access a1Link's value
  setA1(a1: string): void {
    a1Link = a1;
    if(a1Link == 'true' && a2Link == 'true' && b1Link == 'true' && b2Link == 'true' && c1Link == 'true' && c2Link == 'true' && d1Link == 'true' && d2Link == 'true' && e1Link == 'true' && e2Link == 'true'){
      this.navCtrl.push(LoginPasswordPage);
      this.setGlobalVarTrue();
    }
    
  }
  setA2(a2: string): void {
    a2Link = a2;
    if(a1Link == 'true' && a2Link == 'true' && b1Link == 'true' && b2Link == 'true' && c1Link == 'true' && c2Link == 'true' && d1Link == 'true' && d2Link == 'true' && e1Link == 'true' && e2Link == 'true'){
      this.navCtrl.push(LoginPasswordPage);
      this.setGlobalVarTrue();
    }
  }

  setB1(b1: string): void {
    b1Link = b1;
    if(a1Link == 'true' && a2Link == 'true' && b1Link == 'true' && b2Link == 'true' && c1Link == 'true' && c2Link == 'true' && d1Link == 'true' && d2Link == 'true' && e1Link == 'true' && e2Link == 'true'){
      this.navCtrl.push(LoginPasswordPage);
      this.setGlobalVarTrue();
    }
  
  }
  setB2(b2: string): void {
    b2Link = b2;
    if(a1Link == 'true' && a2Link == 'true' && b1Link == 'true' && b2Link == 'true' && c1Link == 'true' && c2Link == 'true' && d1Link == 'true' && d2Link == 'true' && e1Link == 'true' && e2Link == 'true'){
      this.navCtrl.push(LoginPasswordPage);
      this.setGlobalVarTrue();
    }
    
  }
   setC1(c1: string): void {
    c1Link = c1;
    if(a1Link == 'true' && a2Link == 'true' && b1Link == 'true' && b2Link == 'true' && c1Link == 'true' && c2Link == 'true' && d1Link == 'true' && d2Link == 'true' && e1Link == 'true' && e2Link == 'true'){
      this.navCtrl.push(LoginPasswordPage);
      this.setGlobalVarTrue();
    }
 
  }
  setC2(c2: string): void {
    c2Link = c2;
    if(a1Link == 'true' && a2Link == 'true' && b1Link == 'true' && b2Link == 'true' && c1Link == 'true' && c2Link == 'true' && d1Link == 'true' && d2Link == 'true' && e1Link == 'true' && e2Link == 'true'){
      this.navCtrl.push(LoginPasswordPage);
      this.setGlobalVarTrue();
    }
  }
  setD1(d1: string): void {
    d1Link = d1;
    if(a1Link == 'true' && a2Link == 'true' && b1Link == 'true' && b2Link == 'true' && c1Link == 'true' && c2Link == 'true' && d1Link == 'true' && d2Link == 'true' && e1Link == 'true' && e2Link == 'true'){
      this.navCtrl.push(LoginPasswordPage);
      this.setGlobalVarTrue();
    }
 
  }
  setD2(d2: string): void {
    d2Link = d2;
    if(a1Link == 'true' && a2Link == 'true' && b1Link == 'true' && b2Link == 'true' && c1Link == 'true' && c2Link == 'true' && d1Link == 'true' && d2Link == 'true' && e1Link == 'true' && e2Link == 'true'){
      this.navCtrl.push(LoginPasswordPage);
      this.setGlobalVarTrue();
    }
  }

  setE1(e1: string): void {
    e1Link = e1;
    if(a1Link == 'true' && a2Link == 'true' && b1Link == 'true' && b2Link == 'true' && c1Link == 'true' && c2Link == 'true' && d1Link == 'true' && d2Link == 'true' && e1Link == 'true' && e2Link == 'true'){
      this.navCtrl.push(LoginPasswordPage);
      this.setGlobalVarTrue();
    }
 
  }
  setE2(e2: string): void {
    e2Link = e2;
    if(a1Link == 'true' && a2Link == 'true' && b1Link == 'true' && b2Link == 'true' && c1Link == 'true' && c2Link == 'true' && d1Link == 'true' && d2Link == 'true' && e1Link == 'true' && e2Link == 'true'){
      this.navCtrl.push(LoginPasswordPage);
      this.setGlobalVarTrue();
    }
  }

  setGlobalVarTrue() {
    this.globalVars.loginState = true;
  }
   
  solvedPuzzle() {
    this.navCtrl.push(LoginPasswordPage);
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad LoginPage');
    //find out if the user has already done the sliding puzzle
  }
}
