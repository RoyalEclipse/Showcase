package com.semestral.eshop.domain.dto;

import java.util.List;

public class WarehouseDto {
    private Long id;
    private String coordinates;
    private List<Long> availableProducts;

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

    public List<Long> getAvailableProducts() {
        return availableProducts;
    }

    public void setAvailableProducts(List<Long> availableProducts) {
        this.availableProducts = availableProducts;
    }
}