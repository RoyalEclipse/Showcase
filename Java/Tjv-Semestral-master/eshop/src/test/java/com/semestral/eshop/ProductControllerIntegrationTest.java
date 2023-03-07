//package com.semestral.eshop;
//
//import com.semestral.eshop.controller.ProductController;
//import com.semestral.eshop.domain.Product;
//import com.semestral.eshop.service.ProductService;
//import org.junit.jupiter.api.Test;
//import org.mockito.InjectMocks;
//import org.springframework.beans.factory.annotation.Autowired;
//import org.springframework.boot.test.context.SpringBootTest;
//import org.springframework.boot.test.mock.mockito.MockBean;
//import org.springframework.boot.test.web.client.TestRestTemplate;
//import org.springframework.http.HttpStatus;
//import org.springframework.http.ResponseEntity;
//
//import java.util.Optional;
//
//import static org.assertj.core.api.AssertionsForClassTypes.assertThat;
//import static org.mockito.Mockito.doNothing;
//import static org.mockito.Mockito.when;
//
//@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
//public class ProductControllerIntegrationTest {
//
//    @MockBean
//    private ProductService productService;
//
//    @Autowired
//    @InjectMocks
//    private ProductController productController;
//
//    @Autowired
//    TestRestTemplate testRestTemplate;
//
//    @Test
//    void noContent() throws Exception {
//
//        when(productService.findById(1L)).thenReturn(Optional.of(new Product()));
//        doNothing().when(productService).delete(1L);
//
//        ResponseEntity<Void> response = testRestTemplate
//                .delete("/product/1", Void.class);
//
//        assertThat(response.getStatusCode()).isEqualTo(HttpStatus.NO_CONTENT);
//    }
//
//    @Test
//    void notFound() throws Exception {
//
//        when(productService.findById(1L)).thenReturn(Optional.empty());
//        doNothing().when(productService).delete(1L);
//
//        ResponseEntity<Void> response = testRestTemplate
//                .delete("/product/1", Void.class);
//
//        assertThat(response.getStatusCode()).isEqualTo(HttpStatus.NOT_FOUND);
//    }
//}
