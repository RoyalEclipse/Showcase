package com.semestral.eshop.domain.dto;

import java.util.List;

public class SiteOrderDto {
    private Long id;
    private String dateCreated;
    private String deliverTo;
    private int eta;
    private Long fromSiteUser;
    private List<Long> Products;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getDateCreated() {
        return dateCreated;
    }

    public void setDateCreated(String dateCreated) {
        this.dateCreated = dateCreated;
    }

    public String getDeliverTo() {
        return deliverTo;
    }

    public void setDeliverTo(String deliverTo) {
        this.deliverTo = deliverTo;
    }

    public int getEta() {
        return eta;
    }

    public void setEta(int eta) {
        this.eta = eta;
    }

    public Long getFromSiteUser() {
        return fromSiteUser;
    }

    public void setFromSiteUser(Long fromSiteUser) {
        this.fromSiteUser = fromSiteUser;
    }

    public List<Long> getProducts() {
        return Products;
    }

    public void setProducts(List<Long> products) {
        Products = products;
    }
}