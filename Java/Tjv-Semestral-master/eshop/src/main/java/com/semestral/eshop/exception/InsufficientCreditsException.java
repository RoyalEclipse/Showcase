package com.semestral.eshop.exception;

public class InsufficientCreditsException extends RuntimeException{
    public InsufficientCreditsException(String message) {
        super(message);
    }
}
