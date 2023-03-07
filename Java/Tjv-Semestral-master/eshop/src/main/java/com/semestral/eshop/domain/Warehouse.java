package com.semestral.eshop.domain;

import javax.persistence.*;
import java.util.List;

@Entity
public class Warehouse {

    @Id
    @GeneratedValue
    private Long id;

    @Column(nullable=false)
    private String coordinates;

    @ManyToMany(mappedBy = "availableAt")
    private List<Product> availableProducts;

    public Warehouse() {
    }

    public Warehouse(String coordinates, List<Product> availableProducts) {
        this.coordinates = coordinates;
        this.availableProducts = availableProducts;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getCoordinates() {
        return coordinates;
    }

    public void setCoordinates(String coordinates) {
        this.coordinates = coordinates;
    }

    public List<Product> getAvailableProducts() {
        return availableProducts;
    }

    public void setAvailableProducts(List<Product> availableProducts) {
        this.availableProducts = availableProducts;
    }
}

