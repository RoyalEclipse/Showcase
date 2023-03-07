package com.semestral.eshop.repository;

import com.semestral.eshop.domain.SiteOrder;
import org.springframework.data.jpa.repository.JpaRepository;

public interface OrderRepository extends JpaRepository<SiteOrder, Long> {
}
