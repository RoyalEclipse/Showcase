package com.semestral.eshop.domain;

import javax.persistence.*;
import java.util.List;

@Entity
public class SiteUser {
    @Id
    @GeneratedValue
    private Long id;

    @Column(nullable=false)
    private String name;
    @Column(nullable=false)
    private String surname;
    @Column(nullable=false)
    private String email;
    @Column(nullable=false)
    private String phoneNumber;
    @Column(nullable=false)
    private int accessPrivileges;
    @Column(nullable=false)
    private long credits;

    @Column(nullable=false)
    private String password;

    @OneToMany(mappedBy = "fromSiteUser")
    private List<SiteOrder> SiteOrders;

    public SiteUser() {
    }

    public SiteUser(String name, String surname, String email, String phoneNumber, int accessPrivileges, long credits, List<SiteOrder> SiteOrders, String password) {
        this.name = name;
        this.surname = surname;
        this.email = email;
        this.phoneNumber = phoneNumber;
        this.accessPrivileges = accessPrivileges;
        this.credits = credits;
        this.SiteOrders = SiteOrders;
        this.password = password;
    }

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

    public List<SiteOrder> getOrders() {
        return SiteOrders;
    }

    public void setOrders(List<SiteOrder> SiteOrders) {
        this.SiteOrders = SiteOrders;
    }
}