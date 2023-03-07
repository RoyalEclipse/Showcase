package com.semestral.eshop.domain;

import javax.persistence.*;
import java.util.List;

@Entity
public class Product {
    @Id
    @GeneratedValue
    private Long id;

    @Column(nullable=false)
    private String name;
    @Column(nullable=false)
    private String description;
    @Column(nullable=false)
    private String imageUrl;
    @Column(nullable=false)
    private int price;
    @ManyToOne
    private SiteOrder fromSiteOrder;

    @ManyToMany
    @JoinTable(name = "product_warehouse",
            joinColumns = @JoinColumn(name = "product_id"),
            inverseJoinColumns = @JoinColumn(name = "warehouse_id"))
    private List<Warehouse> availableAt;

    public Product() {
    }

    public SiteOrder getFromOrder() {
        return fromSiteOrder;
    }

    public void setFromOrder(SiteOrder fromSiteOrder) {
        this.fromSiteOrder = fromSiteOrder;
    }

    public List<Warehouse> getAvailableAt() {
        return availableAt;
    }

    public void setAvailableAt(List<Warehouse> availableAt) {
        this.availableAt = availableAt;
    }

    public Product(String name, String description, String imageUrl, int price, SiteOrder fromSiteOrder, List<Warehouse> availableAt) {
        this.name = name;
        this.description = description;
        this.imageUrl = imageUrl;
        this.price = price;
        this.fromSiteOrder = fromSiteOrder;
        this.availableAt = availableAt;
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

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getImageUrl() {
        return imageUrl;
    }

    public void setImageUrl(String imageUrl) {
        this.imageUrl = imageUrl;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }
}