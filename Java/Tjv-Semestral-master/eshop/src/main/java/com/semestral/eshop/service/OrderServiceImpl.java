package com.semestral.eshop.service;

import com.semestral.eshop.domain.Product;
import com.semestral.eshop.domain.SiteOrder;
import com.semestral.eshop.domain.SiteUser;
import com.semestral.eshop.domain.Warehouse;
import com.semestral.eshop.domain.dto.SiteOrderRequest;
import com.semestral.eshop.exception.InsufficientCreditsException;
import com.semestral.eshop.repository.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.persistence.EntityNotFoundException;
import java.sql.Timestamp;
import java.util.List;
import java.util.Optional;

@Service
public class OrderServiceImpl implements OrderService{
    private final OrderRepository orderRepository;
    private final UserRepository userRepository;
    private final ProductRepository productRepository;
    private final WarehouseRepositoryCustom warehouseRepositoryCustom;
    private final WarehouseRepository warehouseRepository;

    @Autowired
    public OrderServiceImpl(OrderRepository orderRepository,
                            UserRepository userRepository,
                            ProductRepository productRepository,
                            WarehouseRepositoryCustom warehouseRepositoryCustom,
                            WarehouseRepository warehouseRepository) {
        this.orderRepository = orderRepository;
        this.userRepository = userRepository;
        this.productRepository = productRepository;
        this.warehouseRepositoryCustom = warehouseRepositoryCustom;
        this.warehouseRepository = warehouseRepository;
    }
    @Override
    public SiteOrder create(SiteOrderRequest toAdd) {
        Long targetId = toAdd.getSiteUserId();
        SiteUser targetUser = userRepository.findById(targetId).orElseThrow(() -> new EntityNotFoundException("User not found"));

        List<Product> products = productRepository.findAllById(toAdd.getProductIds());
        long priceTotal = products.stream().mapToLong(Product::getPrice).sum();

        if( priceTotal > targetUser.getCredits() ) {
            throw new InsufficientCreditsException("Not enough credits");
        }

        targetUser.setCredits( targetUser.getCredits() - priceTotal);
        userRepository.save(targetUser);

        SiteOrder toSave = new SiteOrder();
        toSave.setFromUser(targetUser);
        toSave.setDeliverTo(toAdd.getDeliverTo());
        toSave.setProducts( products );
        products.forEach(product -> product.setFromOrder(toSave) );

        Warehouse furthestWarehouse = warehouseRepositoryCustom.calculateFurthest(toAdd.getDeliverTo(), products);
        toSave.setEta( warehouseRepositoryCustom.calculateTravelDistance(toAdd.getDeliverTo(), furthestWarehouse.getCoordinates() ) );
        Timestamp time = new Timestamp(System.currentTimeMillis() );

        toSave.setDateCreated( time.toString() );

        return orderRepository.save(toSave);
    }

    @Override
    public SiteOrder update(SiteOrder toUpdate) {
        return orderRepository.save(toUpdate);
    }

    @Override
    public void delete(Long toDelete) {
        orderRepository.deleteById(toDelete);
    }

    @Override
    public Optional<SiteOrder> findById(Long toFind) {
        return orderRepository.findById(toFind);
    }

    @Override
    public List<SiteOrder> findAll() {
        return orderRepository.findAll();
    }
}
