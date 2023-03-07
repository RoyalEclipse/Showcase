package com.semestral.eshop.domain;

import javax.persistence.*;
import java.util.List;

@Entity
public class SiteOrder {
    @Id
    @GeneratedValue
    private Long id;
    @Column(nullable=false)
    private String dateCreated;
    @Column(nullable=false)
    private String deliverTo;
    @Column(nullable=false)
    private int eta;

    @ManyToOne
    private SiteUser fromSiteUser;

    @OneToMany(mappedBy = "fromSiteOrder")
    private List<Product> Products;

    public SiteOrder() {
    }

    public SiteOrder(String dateCreated, String deliverTo, int eta, SiteUser fromSiteUser, List<Product> Products) {
        this.dateCreated = dateCreated;
        this.deliverTo = deliverTo;
        this.eta = eta;
        this.fromSiteUser = fromSiteUser;
        this.Products = Products;
    }

    public List<Product> getProducts() {
        return Products;
    }

    public void setProducts(List<Product> Products) {
        this.Products = Products;
    }

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

    public SiteUser getFromUser() {
        return fromSiteUser;
    }

    public void setFromUser(SiteUser fromSiteUser) {
        this.fromSiteUser = fromSiteUser;
    }
}