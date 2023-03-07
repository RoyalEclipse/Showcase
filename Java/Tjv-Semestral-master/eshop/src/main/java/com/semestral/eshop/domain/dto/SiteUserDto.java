package com.semestral.eshop.domain.dto;

import java.util.List;

public class SiteUserDto {
    private Long id;
    private String name;
    private String surname;
    private String email;
    private String phoneNumber;
    private int accessPrivileges;
    private long credits;
    private List<Long> siteOrders;

    private String password;

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public int getAccessPrivileges() {
        return accessPrivileges;
    }

    public void setAccessPrivileges(int accessPrivileges) {
        this.accessPrivileges = accessPrivileges;
    }

    public long getCredits() {
        return credits;
    }

    public void setCredits(long credits) {
        this.credits = credits;
    }

    public List<Long> getSiteOrders() {
        return siteOrders;
    }

    public void setSiteOrders(List<Long> siteOrders) {
        this.siteOrders = siteOrders;
    }
}