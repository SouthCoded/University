package com.trafficmon;

public class CalculateChargeCalledMoreThanOneException extends RuntimeException{
    public CalculateChargeCalledMoreThanOneException(String errorMessage){
        super(errorMessage);
    }
}
