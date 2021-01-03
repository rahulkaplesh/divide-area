import { ComponentFixture, TestBed } from '@angular/core/testing';

import { PolygonAreaComponent } from './polygon-area.component';

describe('PolygonAreaComponent', () => {
  let component: PolygonAreaComponent;
  let fixture: ComponentFixture<PolygonAreaComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ PolygonAreaComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(PolygonAreaComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
