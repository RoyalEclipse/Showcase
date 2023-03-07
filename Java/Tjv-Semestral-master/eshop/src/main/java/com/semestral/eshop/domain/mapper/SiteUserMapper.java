package com.semestral.eshop.domain.mapper;

import com.semestral.eshop.domain.SiteOrder;
import com.semestral.eshop.domain.SiteUser;
import com.semestral.eshop.domain.dto.SiteUserDto;
import com.semestral.eshop.repository.OrderRepository;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Optional;

@Component
public class SiteUserMapper {
    private final OrderRepository orderRepository;

    public SiteUserMapper(OrderRepository orderRepository) {
        this.orderRepository = orderRepository;
    }

    public SiteUserDto toDto(SiteUser siteUser){
        SiteUserDto temp = new SiteUserDto();
        temp.setCredits(siteUser.getCredits());
        temp.setEmail(siteUser.getEmail());
        temp.setId(siteUser.getId());
        temp.setName(siteUser.getName());
        temp.setSurname(siteUser.getSurname());
        temp.setAccessPrivileges(siteUser.getAccessPrivileges());
        temp.setPhoneNumber(siteUser.getPhoneNumber());
        temp.setPassword(siteUser.getPassword());

        List<Long> foundIds = new ArrayList<>();
        if( siteUser.getOrders() != null && ! siteUser.getOrders().isEmpty()){
            for(SiteOrder order : siteUser.getOrders()){
                foundIds.add(order.getId());
            }
        }

        temp.setSiteOrders(foundIds);

        return temp;
    }
    public SiteUser fromDto(SiteUserDto siteUserDto){
        SiteUser temp = new SiteUser();
        temp.setCredits(siteUserDto.getCredits());
        temp.setEmail(siteUserDto.getEmail());
        temp.setId(siteUserDto.getId());
        temp.setName(siteUserDto.getName());
        temp.setSurname(siteUserDto.getSurname());
        temp.setAccessPrivileges(siteUserDto.getAccessPrivileges());
        temp.setPhoneNumber(siteUserDto.getPhoneNumber());
        temp.setPassword(siteUserDto.getPassword());

        List<SiteOrder> foundOrders = new ArrayList<>();
        if( siteUserDto.getSiteOrders().isEmpty()){
            for( Long id : siteUserDto.getSiteOrders()){
                Optional<SiteOrder> found = orderRepository.findById(id);
                if (found.isPresent()){
                    foundOrders.add(found.get());
                }
                else{
                    throw new NoSuchElementException("no such order found");
                }
            }
        }

        temp.setOrders(foundOrders);
        return temp;
    }
}
