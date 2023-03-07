package com.semestral.eshop.domain.mapper;

import com.semestral.eshop.domain.Product;
import com.semestral.eshop.domain.SiteOrder;
import com.semestral.eshop.domain.SiteUser;
import com.semestral.eshop.domain.dto.SiteOrderDto;
import com.semestral.eshop.repository.ProductRepository;
import com.semestral.eshop.repository.UserRepository;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Optional;

@Component

public class SiteOrderMapper {
    private final UserRepository userRepository;
    private final ProductRepository productRepository;

    public SiteOrderMapper(UserRepository userRepository,
                           ProductRepository productRepository) {
        this.userRepository = userRepository;
        this.productRepository = productRepository;
    }

    public SiteOrderDto toDto(SiteOrder siteOrder){
        SiteOrderDto temp = new SiteOrderDto();
        temp.setEta(siteOrder.getEta());
        temp.setDateCreated(siteOrder.getDateCreated());
        temp.setDeliverTo(siteOrder.getDeliverTo());
        temp.setId(siteOrder.getId());

        List<Long> productIds = new ArrayList<>();
        siteOrder.getProducts().forEach( product -> productIds.add(product.getId()) );
        temp.setProducts(productIds);

        temp.setFromSiteUser(siteOrder.getFromUser().getId());
        return temp;
    }
    public SiteOrder fromDto(SiteOrderDto siteOrderDto){
        SiteOrder temp = new SiteOrder();
        temp.setEta(siteOrderDto.getEta());
        temp.setDateCreated(siteOrderDto.getDateCreated());
        temp.setDeliverTo(siteOrderDto.getDeliverTo());
        temp.setId(siteOrderDto.getId());

        List<Product> products = new ArrayList<>();
        for( Long id : siteOrderDto.getProducts() ){
            Optional<Product> found = productRepository.findById(id);
            if(found.isPresent()){
                products.add(found.get());
            }
            else{
                throw new NoSuchElementException("no such product");
            }
        }

        temp.setProducts(products);


        SiteUser foundId = userRepository.findById(siteOrderDto.getFromSiteUser() ).orElseThrow();
        temp.setFromUser(foundId);
        return temp;
    }
}
