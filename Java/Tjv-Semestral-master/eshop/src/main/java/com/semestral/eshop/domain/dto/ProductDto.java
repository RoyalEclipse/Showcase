package com.semestral.eshop.domain.dto;

import java.util.List;

public class ProductDto {
    private Long id;
    private String name;
    private String description;
    private String imageUrl;
    private int price;
    private Long fromSiteOrder;
    private List<Long> availableAt;

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

    public Long getFromSiteOrder() {
        return fromSiteOrder;
    }

    public void setFromSiteOrder(Long fromSiteOrder) {
        this.fromSiteOrder = fromSiteOrder;
    }

    public List<Long> getAvailableAt() {
        return availableAt;
    }

    public void setAvailableAt(List<Long> availableAt) {
        this.availableAt = availableAt;
    }
}